 * originally written at the National Center for Supercomputing Applications,
 * University of Illinois, Urbana-Champaign.
 */

/*
 * mod_isapi.c - Internet Server Application (ISA) module for Apache
 * by Alexei Kosut <akosut@apache.org>
 *
 * This module implements Microsoft's ISAPI, allowing Apache (when running
 * under Windows) to load Internet Server Applications (ISAPI extensions).
 * It implements all of the ISAPI 2.0 specification, except for the 
 * "Microsoft-only" extensions dealing with asynchronous I/O. All ISAPI
 * extensions that use only synchronous I/O and are compatible with the
 * ISAPI 2.0 specification should work (most ISAPI 1.0 extensions should
 * function as well).
 *
 * To load, simply place the ISA in a location in the document tree.
 * Then add an "AddHandler isapi-isa dll" into your config file.
 * You should now be able to load ISAPI DLLs just be reffering to their
 * URLs. Make sure the ExecCGI option is active in the directory
 * the ISA is in.
 */

#include "apr_strings.h"
#include "apr_portable.h"
#include "apr_buckets.h"
#include "ap_config.h"
#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_protocol.h"
#include "http_request.h"
#include "http_log.h"
#include "util_script.h"
#include "mod_core.h"

/* We use the exact same header file as the original */
#include <HttpExt.h>

#if !defined(HSE_REQ_MAP_URL_TO_PATH_EX) \
 || !defined(HSE_REQ_SEND_RESPONSE_HEADER_EX)
#pragma message("WARNING: This build of Apache is missing the recent changes")
#pragma message("in the Microsoft Win32 Platform SDK; some mod_isapi features")
#pragma message("will be disabled.  To obtain the latest Platform SDK files,")
#pragma message("please refer to:")
#pragma message("http://msdn.microsoft.com/downloads/sdks/platform/platform.asp")
#endif

/* TODO: Unknown errors that must be researched for correct codes */

#define TODO_ERROR 1

/* Seems IIS does not enforce the requirement for \r\n termination on HSE_REQ_SEND_RESPONSE_HEADER,
   define this to conform */
#define RELAX_HEADER_RULE

module AP_MODULE_DECLARE_DATA isapi_module;

/* Declare the ISAPI functions */

BOOL WINAPI GetServerVariable (HCONN hConn, LPSTR lpszVariableName,
                               LPVOID lpvBuffer, LPDWORD lpdwSizeofBuffer);
BOOL WINAPI WriteClient (HCONN ConnID, LPVOID Buffer, LPDWORD lpdwBytes,
                         DWORD dwReserved);
BOOL WINAPI ReadClient (HCONN ConnID, LPVOID lpvBuffer, LPDWORD lpdwSize);
BOOL WINAPI ServerSupportFunction (HCONN hConn, DWORD dwHSERequest,
                                   LPVOID lpvBuffer, LPDWORD lpdwSize,
                                   LPDWORD lpdwDataType);

/* Our isapi server config structure */

typedef struct {
    apr_array_header_t *loaded;
    DWORD ReadAheadBuffer;
    int LogNotSupported;
    int AppendLogToErrors;
    int AppendLogToQuery;
} isapi_server_conf;

/* Our loaded isapi module description structure */

typedef struct {
    const char *filename;
    apr_dso_handle_t *handle;
    HSE_VERSION_INFO *pVer;
    PFN_GETEXTENSIONVERSION GetExtensionVersion;
    PFN_HTTPEXTENSIONPROC   HttpExtensionProc;
    PFN_TERMINATEEXTENSION  TerminateExtension;
    int   refcount;
    DWORD timeout;
    BOOL  fakeasync;
    DWORD reportversion;
} isapi_loaded;

/* Our "Connection ID" structure */

typedef struct {
    LPEXTENSION_CONTROL_BLOCK ecb;
    isapi_server_conf *sconf;
    isapi_loaded *isa;
    request_rec  *r;
    PFN_HSE_IO_COMPLETION completion;
    PVOID  completion_arg;
    HANDLE complete;
} isapi_cid;

static void *create_isapi_server_config(apr_pool_t *p, server_rec *s)
{
    isapi_server_conf *sconf = apr_palloc(p, sizeof(isapi_server_conf));
    sconf->loaded = apr_array_make(p, 20, sizeof(isapi_loaded*));
    
    sconf->ReadAheadBuffer = 49152;
    sconf->LogNotSupported    = -1;
    sconf->AppendLogToErrors   = 0;
    sconf->AppendLogToQuery    = 0;

    return sconf;
}

static int compare_loaded(const void *av, const void *bv)
{
    const isapi_loaded **a = av;
    const isapi_loaded **b = bv;

    return strcmp((*a)->filename, (*b)->filename);
}

static int isapi_post_config(apr_pool_t *p, apr_pool_t *plog,
                             apr_pool_t *ptemp, server_rec *s)
{
    isapi_server_conf *sconf = ap_get_module_config(s->module_config, 
                                                    &isapi_module);
    isapi_loaded **elts = (isapi_loaded **)sconf->loaded->elts;
    int nelts = sconf->loaded->nelts;

    /* sort the elements of the main_server, by filename */
    qsort(elts, nelts, sizeof(isapi_loaded*), compare_loaded);

    /* and make all virtualhosts share the same */
    for (s = s->next; s; s = s->next) {
	ap_set_module_config(s->module_config, &isapi_module, sconf);
    }
    return OK;
}

static apr_status_t isapi_unload(isapi_loaded* isa, int force);

static apr_status_t cleanup_isapi(void *isa)
{
    return isapi_unload((isapi_loaded*) isa, TRUE);
}

static apr_status_t isapi_load(apr_pool_t *p, isapi_server_conf *sconf, 
                               request_rec *r, const char *fpath, 
                               isapi_loaded** isa)
{
    isapi_loaded **found = (isapi_loaded **)sconf->loaded->elts;
    apr_status_t rv;
    int n;

    for (n = 0; n < sconf->loaded->nelts; ++n) {
        if (strcasecmp(fpath, (*found)->filename) == 0) {
            break;
        }
        ++found;
    }
    
    if (n < sconf->loaded->nelts) 
    {
        *isa = *found;
        if ((*isa)->handle) 
        {
            ++(*isa)->refcount;
            return APR_SUCCESS;
        }
        /* Otherwise we fall through and have to reload the resource
         * into this existing mod_isapi cache bucket.
         */
    }
    else
    {
        *isa = apr_pcalloc(p, sizeof(isapi_module));
        (*isa)->filename = fpath;
        (*isa)->pVer = apr_pcalloc(p, sizeof(HSE_VERSION_INFO));
    
        /* TODO: These need to become overrideable, so that we
         * assure a given isapi can be fooled into behaving well.
         */
        (*isa)->timeout = INFINITE; /* microsecs */
        (*isa)->fakeasync = TRUE;
        (*isa)->reportversion = MAKELONG(0, 5); /* Revision 5.0 */
    }
    
    rv = apr_dso_load(&(*isa)->handle, fpath, p);
    if (rv)
    {
        ap_log_rerror(APLOG_MARK, APLOG_ALERT, rv, r,
                      "ISAPI %s failed to load", fpath);
        (*isa)->handle = NULL;
        return rv;
    }

    rv = apr_dso_sym((void**)&(*isa)->GetExtensionVersion, (*isa)->handle,
                     "GetExtensionVersion");
    if (rv)
    {
        ap_log_rerror(APLOG_MARK, APLOG_ALERT, rv, r,
                      "ISAPI %s is missing GetExtensionVersion()",
                      fpath);
        apr_dso_unload((*isa)->handle);
        (*isa)->handle = NULL;
        return rv;
    }

    rv = apr_dso_sym((void**)&(*isa)->HttpExtensionProc, (*isa)->handle,
                     "HttpExtensionProc");
    if (rv)
    {
        ap_log_rerror(APLOG_MARK, APLOG_ALERT, rv, r,
                      "ISAPI %s is missing HttpExtensionProc()",
                      fpath);
        apr_dso_unload((*isa)->handle);
        (*isa)->handle = NULL;
        return rv;
    }

    /* TerminateExtension() is an optional interface */
    rv = apr_dso_sym((void**)&(*isa)->TerminateExtension, (*isa)->handle,
                     "TerminateExtension");
    SetLastError(0);

    /* Run GetExtensionVersion() */
    if (!((*isa)->GetExtensionVersion)((*isa)->pVer)) {
        apr_status_t rv = apr_get_os_error();
        ap_log_rerror(APLOG_MARK, APLOG_ALERT, rv, r,
                      "ISAPI %s call GetExtensionVersion() failed", 
                      fpath);
        apr_dso_unload((*isa)->handle);
        (*isa)->handle = NULL;
        return rv;
    }

    ++(*isa)->refcount;

    apr_pool_cleanup_register(p, *isa, cleanup_isapi, 
                                   apr_pool_cleanup_null);

    return APR_SUCCESS;
}

static apr_status_t isapi_unload(isapi_loaded* isa, int force)
{
    /* All done with the DLL... get rid of it...
     *
     * If optionally cached, pass HSE_TERM_ADVISORY_UNLOAD,
     * and if it returns TRUE, unload, otherwise, cache it.
     */
    if (((--isa->refcount > 0) && !force) || !isa->handle)
        return APR_SUCCESS;
    if (isa->TerminateExtension) {
        if (force)
            (*isa->TerminateExtension)(HSE_TERM_MUST_UNLOAD);
        else if (!(*isa->TerminateExtension)(HSE_TERM_ADVISORY_UNLOAD))
            return APR_EGENERAL;
    }
    apr_dso_unload(isa->handle);
    isa->handle = NULL;
    return APR_SUCCESS;
}

apr_status_t isapi_handler (request_rec *r)
{
    isapi_server_conf * sconf;
    apr_table_t *e;
    apr_status_t rv;
    isapi_loaded *isa;
    isapi_cid *cid;
    const char *val;
    DWORD read;
    int res;
    
    if(strcmp(r->handler, "isapi-isa"))
        return DECLINED;    

    sconf = ap_get_module_config(r->server->module_config, &isapi_module);
    e = r->subprocess_env;

    /* Use similar restrictions as CGIs
     *
     * If this fails, it's pointless to load the isapi dll.
     */
    if (!(ap_allow_options(r) & OPT_EXECCGI))
        return HTTP_FORBIDDEN;

    if (r->finfo.filetype == APR_NOFILE)
        return HTTP_NOT_FOUND;

    if (r->finfo.filetype != APR_REG)
        return HTTP_FORBIDDEN;

    if ((r->used_path_info == AP_REQ_REJECT_PATH_INFO) &&
        r->path_info && *r->path_info)
    {
        /* default to accept */
        return HTTP_NOT_FOUND;
    }

    /* Load the isapi extention without caching (sconf == NULL) 
     * but note that we will recover an existing cached module.
     */
    if (isapi_load(r->pool, sconf, r, r->filename, &isa) != APR_SUCCESS)
        return HTTP_INTERNAL_SERVER_ERROR;
        
    /* Set up variables */
    ap_add_common_vars(r);
    ap_add_cgi_vars(r);
    apr_table_setn(e, "UNMAPPED_REMOTE_USER", "REMOTE_USER");
    if ((val = apr_table_get(e, "HTTPS")) && strcmp(val, "on"))
        apr_table_setn(e, "SERVER_PORT_SECURE", "1");
    else
        apr_table_setn(e, "SERVER_PORT_SECURE", "0");
    apr_table_setn(e, "URL", r->uri);

    /* Set up connection structure and ecb */
    cid = apr_pcalloc(r->pool, sizeof(isapi_cid));
    cid->sconf = ap_get_module_config(r->server->module_config, &isapi_module);

    cid->ecb = apr_pcalloc(r->pool, sizeof(struct _EXTENSION_CONTROL_BLOCK));
    cid->ecb->ConnID = (HCONN)cid;
    cid->isa = isa;
    cid->r = r;
    cid->r->status = 0;
    cid->complete = NULL;
    cid->completion = NULL;
    
    cid->ecb->cbSize = sizeof(EXTENSION_CONTROL_BLOCK);
    cid->ecb->dwVersion = isa->reportversion;
    cid->ecb->dwHttpStatusCode = 0;
    strcpy(cid->ecb->lpszLogData, "");
    // TODO: are copies really needed here?
    cid->ecb->lpszMethod = apr_pstrdup(r->pool, (char*) r->method);
    cid->ecb->lpszQueryString = apr_pstrdup(r->pool, 
                                (char*) apr_table_get(e, "QUERY_STRING"));
    cid->ecb->lpszPathInfo = apr_pstrdup(r->pool, 
                             (char*) apr_table_get(e, "PATH_INFO"));
    cid->ecb->lpszPathTranslated = apr_pstrdup(r->pool, 
                                   (char*) apr_table_get(e, "PATH_TRANSLATED"));
    cid->ecb->lpszContentType = apr_pstrdup(r->pool, 
                                (char*) apr_table_get(e, "CONTENT_TYPE"));
    /* Set up the callbacks */
    cid->ecb->GetServerVariable = GetServerVariable;
    cid->ecb->WriteClient = WriteClient;
    cid->ecb->ReadClient = ReadClient;
    cid->ecb->ServerSupportFunction = ServerSupportFunction;

    
    /* Set up client input */
    res = ap_setup_client_block(r, REQUEST_CHUNKED_ERROR);
    if (res) {
        isapi_unload(isa, FALSE);
        return res;
    }

    if (ap_should_client_block(r)) {
        /* Time to start reading the appropriate amount of data,
         * and allow the administrator to tweak the number
         * TODO: add the httpd.conf option for ReadAheadBuffer.
         */
        if (r->remaining) {
            cid->ecb->cbTotalBytes = (apr_size_t)r->remaining;
            if (cid->ecb->cbTotalBytes > cid->sconf->ReadAheadBuffer)
                cid->ecb->cbAvailable = cid->sconf->ReadAheadBuffer;
            else
                cid->ecb->cbAvailable = cid->ecb->cbTotalBytes;
        }
        else
        {
            cid->ecb->cbTotalBytes = 0xffffffff;
            cid->ecb->cbAvailable = cid->sconf->ReadAheadBuffer;
        }

        cid->ecb->lpbData = apr_pcalloc(r->pool, cid->ecb->cbAvailable + 1);

        read = 0;
        while (read < cid->ecb->cbAvailable &&
               ((res = ap_get_client_block(r, cid->ecb->lpbData + read,
                                        cid->ecb->cbAvailable - read)) > 0)) {
            read += res;
        }

        if (res < 0) {
            isapi_unload(isa, FALSE);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        /* Although it's not to spec, IIS seems to null-terminate
         * its lpdData string. So we will too.
         */
        if (res == 0)
            cid->ecb->cbAvailable = cid->ecb->cbTotalBytes = read;
        else
            cid->ecb->cbAvailable = read;
        cid->ecb->lpbData[read] = '\0';
    }
    else {
        cid->ecb->cbTotalBytes = 0;
        cid->ecb->cbAvailable = 0;
        cid->ecb->lpbData = NULL;
    }

    /* All right... try and run the sucker */
    rv = (*isa->HttpExtensionProc)(cid->ecb);

    /* Check for a log message - and log it */
    if (cid->ecb->lpszLogData && *cid->ecb->lpszLogData)
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, 0, r,
                      "ISAPI %s: %s", r->filename, cid->ecb->lpszLogData);

    switch(rv) {
        case 0:  /* Strange, but MS isapi accepts this as success */
        case HSE_STATUS_SUCCESS:
        case HSE_STATUS_SUCCESS_AND_KEEP_CONN:
            /* Ignore the keepalive stuff; Apache handles it just fine without
             * the ISA's "advice".
             * Per Microsoft: "In IIS versions 4.0 and later, the return
             * values HSE_STATUS_SUCCESS and HSE_STATUS_SUCCESS_AND_KEEP_CONN
             * are functionally identical: Keep-Alive connections are
             * maintained, if supported by the client."
             * ... so we were pat all this time
             */
            break;

        case HSE_STATUS_PENDING:    
            /* emulating async behavior...
             *
             * Create a cid->completed event and wait on it for some timeout
             * so that the app thinks is it running async.
             *
             * All async ServerSupportFunction calls will be handled through
             * the registered IO_COMPLETION hook.
             */
            
            if (!isa->fakeasync) {
                if (cid->sconf->LogNotSupported)
                {
                     ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
                                   "ISAPI %s asynch I/O request refused", 
                                   r->filename);
                     cid->r->status = HTTP_INTERNAL_SERVER_ERROR;
                }
            }
            else {
                cid->complete = CreateEvent(NULL, FALSE, FALSE, NULL);
                if (WaitForSingleObject(cid->complete, isa->timeout)
                        == WAIT_TIMEOUT) {
                    /* TODO: Now what... if this hung, then do we kill our own
                     * thread to force its death?  For now leave timeout = -1
                     */
                }
            }
            break;

        case HSE_STATUS_ERROR:    
            /* end response if we have yet to do so.
             */
            cid->r->status = HTTP_INTERNAL_SERVER_ERROR;
            break;

        default:
            /* TODO: log unrecognized retval for debugging 
             */
            cid->r->status = HTTP_INTERNAL_SERVER_ERROR;
            break;
    }

    /* Set the status (for logging) */
    if (cid->ecb->dwHttpStatusCode) {
        cid->r->status = cid->ecb->dwHttpStatusCode;
    }

    /* All done with the DLL... get rid of it... */
    isapi_unload(isa, FALSE);
    
    return OK;		/* NOT r->status, even if it has changed. */
}

BOOL WINAPI GetServerVariable (HCONN hConn, LPSTR lpszVariableName,
                               LPVOID lpvBuffer, LPDWORD lpdwSizeofBuffer)
{
    request_rec *r = ((isapi_cid *)hConn)->r;
    const char *result;
    DWORD len;

    if (!strcmp(lpszVariableName, "ALL_HTTP")) 
    {
        /* lf delimited, colon split, comma seperated and 
         * null terminated list of HTTP_ vars 
         */
        const apr_array_header_t *arr = apr_table_elts(r->subprocess_env);
        const apr_table_entry_t *elts = (const apr_table_entry_t *)arr->elts;
