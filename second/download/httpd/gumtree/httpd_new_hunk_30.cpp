 * originally written at the National Center for Supercomputing Applications,
 * University of Illinois, Urbana-Champaign.
 */

/*
 * mod_isapi.c - Internet Server Application (ISA) module for Apache
 * by Alexei Kosut <akosut@apache.org>, significant overhauls and
 * redesign by William Rowe <wrowe@covalent.net>, and hints from many
 * other developer/users who have hit on specific flaws.
 *
 * This module implements the ISAPI Handler architecture, allowing 
 * Apache to load Internet Server Applications (ISAPI extensions),
 * similar to the support in IIS, Zope, O'Reilly's WebSite and others.
 *
 * It is a complete implementation of the ISAPI 2.0 specification, 
 * except for "Microsoft extensions" to the API which provide 
 * asynchronous I/O.  It is further extended to include additional
 * "Microsoft extentions" through IIS 5.0, with some deficiencies
 * where one-to-one mappings don't exist.
 *
 * Refer to /manual/mod/mod_isapi.html for additional details on
 * configuration and use, but check this source for specific support
 * of the API, 
 */

#include "ap_config.h"
#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_protocol.h"
#include "http_request.h"
#include "http_log.h"
#include "util_script.h"
#include "mod_core.h"
#include "apr_lib.h"
#include "apr_strings.h"
#include "apr_portable.h"
#include "apr_buckets.h"
#include "apr_thread_mutex.h"
#include "apr_thread_rwlock.h"
#include "apr_hash.h"
#include "mod_isapi.h"

/* Retry frequency for a failed-to-load isapi .dll */
#define ISAPI_RETRY apr_time_from_sec(30)

/**********************************************************
 *
 *  ISAPI Module Configuration
 *
 **********************************************************/

module AP_MODULE_DECLARE_DATA isapi_module;

#define ISAPI_UNDEF -1

/* Our isapi per-dir config structure */
typedef struct isapi_dir_conf {
    int read_ahead_buflen;
    int log_unsupported;
    int log_to_errlog;
    int log_to_query;
    int fake_async;
} isapi_dir_conf;

typedef struct isapi_loaded isapi_loaded;

apr_status_t isapi_lookup(apr_pool_t *p, server_rec *s, request_rec *r, 
                          const char *fpath, isapi_loaded** isa);

static void *create_isapi_dir_config(apr_pool_t *p, char *dummy)
{
    isapi_dir_conf *dir = apr_palloc(p, sizeof(isapi_dir_conf));
    
    dir->read_ahead_buflen = ISAPI_UNDEF;
    dir->log_unsupported   = ISAPI_UNDEF;
    dir->log_to_errlog     = ISAPI_UNDEF;
    dir->log_to_query      = ISAPI_UNDEF;
    dir->fake_async        = ISAPI_UNDEF;

    return dir;
}

static void *merge_isapi_dir_configs(apr_pool_t *p, void *base_, void *add_)
{
    isapi_dir_conf *base = (isapi_dir_conf *) base_;
    isapi_dir_conf *add = (isapi_dir_conf *) add_;
    isapi_dir_conf *dir = apr_palloc(p, sizeof(isapi_dir_conf));
    
    dir->read_ahead_buflen = (add->read_ahead_buflen == ISAPI_UNDEF)
                                ? base->read_ahead_buflen
                                 : add->read_ahead_buflen;
    dir->log_unsupported   = (add->log_unsupported == ISAPI_UNDEF)
                                ? base->log_unsupported
                                 : add->log_unsupported;
    dir->log_to_errlog     = (add->log_to_errlog == ISAPI_UNDEF)
                                ? base->log_to_errlog
                                 : add->log_to_errlog;
    dir->log_to_query      = (add->log_to_query == ISAPI_UNDEF)
                                ? base->log_to_query
                                 : add->log_to_query;
    dir->fake_async        = (add->fake_async == ISAPI_UNDEF)
                                ? base->fake_async
                                 : add->fake_async;
    
    return dir;
}

static const char *isapi_cmd_cachefile(cmd_parms *cmd, void *dummy, 
                                       const char *filename)
{
    isapi_loaded *isa;
    apr_finfo_t tmp;
    apr_status_t rv;
    char *fspec;

    /* ### Just an observation ... it would be terribly cool to be
     * able to use this per-dir, relative to the directory block being
     * defined.  The hash result remains global, but shorthand of
     * <Directory "c:/webapps/isapi">
     *     ISAPICacheFile myapp.dll anotherapp.dll thirdapp.dll
     * </Directory>
     * would be very convienent.
     */
    fspec = ap_server_root_relative(cmd->pool, filename);
    if (!fspec) {
	ap_log_error(APLOG_MARK, APLOG_WARNING, APR_EBADPATH, cmd->server,
	             "ISAPI: invalid module path, skipping %s", filename);
	return NULL;
    }
    if ((rv = apr_stat(&tmp, fspec, APR_FINFO_TYPE, 
                      cmd->temp_pool)) != APR_SUCCESS) { 
	ap_log_error(APLOG_MARK, APLOG_WARNING, rv, cmd->server,
	    "ISAPI: unable to stat, skipping %s", fspec);
	return NULL;
    }
    if (tmp.filetype != APR_REG) {
	ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
	    "ISAPI: not a regular file, skipping %s", fspec);
	return NULL;
    }

    /* Load the extention as cached (with null request_rec) */
    rv = isapi_lookup(cmd->pool, cmd->server, NULL, fspec, &isa); 
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, cmd->server,
                     "ISAPI: unable to cache, skipping %s", fspec);
	return NULL;
    }

    return NULL;
}

static const command_rec isapi_cmds[] = {
    AP_INIT_TAKE1("ISAPIReadAheadBuffer", ap_set_int_slot,
        (void *)APR_OFFSETOF(isapi_dir_conf, read_ahead_buflen), 
        OR_FILEINFO, "Maximum client request body to initially pass to the"
                     " ISAPI handler (default: 48192)"),
    AP_INIT_FLAG("ISAPILogNotSupported", ap_set_flag_slot,
        (void *)APR_OFFSETOF(isapi_dir_conf, log_unsupported), 
        OR_FILEINFO, "Log requests not supported by the ISAPI server"
                     " on or off (default: off)"),
    AP_INIT_FLAG("ISAPIAppendLogToErrors", ap_set_flag_slot,
        (void *)APR_OFFSETOF(isapi_dir_conf, log_to_errlog), 
        OR_FILEINFO, "Send all Append Log requests to the error log"
                     " on or off (default: off)"),
    AP_INIT_FLAG("ISAPIAppendLogToQuery", ap_set_flag_slot,
        (void *)APR_OFFSETOF(isapi_dir_conf, log_to_query), 
        OR_FILEINFO, "Append Log requests are concatinated to the query args"
                     " on or off (default: on)"),
    AP_INIT_FLAG("ISAPIFakeAsync", ap_set_flag_slot,
        (void *)APR_OFFSETOF(isapi_dir_conf, fake_async), 
        OR_FILEINFO, "Fake Asynchronous support for isapi callbacks"
                     " on or off [Experimental] (default: off)"),
    AP_INIT_ITERATE("ISAPICacheFile", isapi_cmd_cachefile, NULL, 
        RSRC_CONF, "Cache the specified ISAPI extension in-process"),
    {NULL}
};

/**********************************************************
 *
 *  ISAPI Module Cache handling section
 *
 **********************************************************/

/* Our isapi global config values */
static struct isapi_global_conf {
    apr_pool_t         *pool;
    apr_thread_mutex_t *lock;
    apr_hash_t         *hash;
} loaded;

/* Our loaded isapi module description structure */
struct isapi_loaded {
    const char          *filename;
    apr_thread_rwlock_t *in_progress;
    apr_status_t         last_load_rv;
    apr_time_t           last_load_time;
    apr_dso_handle_t    *handle;
    HSE_VERSION_INFO    *isapi_version;
    apr_uint32_t         report_version;
    apr_uint32_t         timeout;
    PFN_GETEXTENSIONVERSION GetExtensionVersion;
    PFN_HTTPEXTENSIONPROC   HttpExtensionProc;
    PFN_TERMINATEEXTENSION  TerminateExtension;
};

static apr_status_t isapi_unload(isapi_loaded *isa, int force)
{
    /* All done with the DLL... get rid of it...
     *
     * If optionally cached, and we weren't asked to force the unload,
     * pass HSE_TERM_ADVISORY_UNLOAD, and if it returns 1, unload, 
     * otherwise, leave it alone (it didn't choose to cooperate.)
     */
    if (!isa->handle) {
        return APR_SUCCESS;
    }
    if (isa->TerminateExtension) {
        if (force) {
            (*isa->TerminateExtension)(HSE_TERM_MUST_UNLOAD);
        }
        else if (!(*isa->TerminateExtension)(HSE_TERM_ADVISORY_UNLOAD)) {
            return APR_EGENERAL;
        }
    }
    apr_dso_unload(isa->handle);
    isa->handle = NULL;
    return APR_SUCCESS;
}

static apr_status_t cleanup_isapi(void *isa_)
{
    isapi_loaded* isa = (isapi_loaded*) isa_;

    /* We must force the module to unload, we are about 
     * to lose the isapi structure's allocation entirely.
     */
    return isapi_unload(isa, 1);
}

static apr_status_t isapi_load(apr_pool_t *p, server_rec *s, isapi_loaded *isa)
{
    apr_status_t rv;

    isa->isapi_version = apr_pcalloc(p, sizeof(HSE_VERSION_INFO));

    /* TODO: These aught to become overrideable, so that we
     * assure a given isapi can be fooled into behaving well.
     *
     * The tricky bit, they aren't really a per-dir sort of
     * config, they will always be constant across every 
     * reference to the .dll no matter what context (vhost,
     * location, etc) they apply to.
     */
    isa->report_version = MAKELONG(0, 5); /* Revision 5.0 */
    isa->timeout = INFINITE; /* microsecs */
    
    rv = apr_dso_load(&isa->handle, isa->filename, p);
    if (rv)
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "ISAPI: failed to load %s", isa->filename);
        isa->handle = NULL;
        return rv;
    }

    rv = apr_dso_sym((void**)&isa->GetExtensionVersion, isa->handle,
                     "GetExtensionVersion");
    if (rv)
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "ISAPI: missing GetExtensionVersion() in %s",
                     isa->filename);
        apr_dso_unload(isa->handle);
        isa->handle = NULL;
        return rv;
    }

    rv = apr_dso_sym((void**)&isa->HttpExtensionProc, isa->handle,
                     "HttpExtensionProc");
    if (rv)
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "ISAPI: missing HttpExtensionProc() in %s",
                     isa->filename);
        apr_dso_unload(isa->handle);
        isa->handle = NULL;
        return rv;
    }

    /* TerminateExtension() is an optional interface */
    rv = apr_dso_sym((void**)&isa->TerminateExtension, isa->handle,
                     "TerminateExtension");
    SetLastError(0);

    /* Run GetExtensionVersion() */
    if (!(isa->GetExtensionVersion)(isa->isapi_version)) {
        apr_status_t rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "ISAPI: failed call to GetExtensionVersion() in %s", 
                     isa->filename);
        apr_dso_unload(isa->handle);
        isa->handle = NULL;
        return rv;
    }

    apr_pool_cleanup_register(p, isa, cleanup_isapi, 
                              apr_pool_cleanup_null);

    return APR_SUCCESS;
}

apr_status_t isapi_lookup(apr_pool_t *p, server_rec *s, request_rec *r, 
                          const char *fpath, isapi_loaded** isa)
{
    apr_status_t rv;
    const char *key;

    if ((rv = apr_thread_mutex_lock(loaded.lock)) != APR_SUCCESS) {
        return rv;
    }

    *isa = apr_hash_get(loaded.hash, fpath, APR_HASH_KEY_STRING);

    if (*isa) {

        /* If we find this lock exists, use a set-aside copy of gainlock
         * to avoid race conditions on NULLing the in_progress variable 
         * when the load has completed.  Release the global isapi hash
         * lock so other requests can proceed, then rdlock for completion
         * of loading our desired dll or wrlock if we would like to retry
         * loading the dll (because last_load_rv failed and retry is up.)
         */
        apr_thread_rwlock_t *gainlock = (*isa)->in_progress;

        /* gainlock is NULLed after the module loads successfully.
         * This free-threaded module can be used without any locking.
         */
        if (!gainlock) {
            rv = (*isa)->last_load_rv;
            apr_thread_mutex_unlock(loaded.lock);
            return rv;
        }

            
        if ((*isa)->last_load_rv == APR_SUCCESS) {
            apr_thread_mutex_unlock(loaded.lock);
            if ((rv = apr_thread_rwlock_rdlock(gainlock)) 
                    != APR_SUCCESS) {
                return rv;
            }
            rv = (*isa)->last_load_rv;
            apr_thread_rwlock_unlock(gainlock);
            return rv;
        }

        if (apr_time_now() > (*isa)->last_load_time + ISAPI_RETRY) {
        
            /* Remember last_load_time before releasing the global
             * hash lock to avoid colliding with another thread
             * that hit this exception at the same time as our
             * retry attempt, since we unlock the global mutex
             * before attempting a write lock for this module.
             */
            apr_time_t check_time = (*isa)->last_load_time;
            apr_thread_mutex_unlock(loaded.lock);

            if ((rv = apr_thread_rwlock_wrlock(gainlock)) 
                    != APR_SUCCESS) {
                return rv;
            }

            /* If last_load_time is unchanged, we still own this
             * retry, otherwise presume another thread provided 
             * our retry (for good or ill).  Relock the global
             * hash for updating last_load_ vars, so their update
             * is always atomic to the global lock.
             */
            if (check_time == (*isa)->last_load_time) {

                rv = isapi_load(loaded.pool, s, *isa);

                apr_thread_mutex_lock(loaded.lock);
                (*isa)->last_load_rv = rv;
                (*isa)->last_load_time = apr_time_now();
                apr_thread_mutex_unlock(loaded.lock);
            }
            else {
                rv = (*isa)->last_load_rv;
            }
            apr_thread_rwlock_unlock(gainlock);

            return rv;
        }

        /* We haven't hit timeup on retry, let's grab the last_rv
         * within the hash mutex before unlocking.
         */
        rv = (*isa)->last_load_rv;
        apr_thread_mutex_unlock(loaded.lock);

        return rv;
    }

    /* If the module was not found, it's time to create a hash key entry
     * before releasing the hash lock to avoid multiple threads from 
     * loading the same module.
     */
    key = apr_pstrdup(loaded.pool, fpath);
    *isa = apr_pcalloc(loaded.pool, sizeof(isapi_loaded));
    (*isa)->filename = key;
    if (r) {
        /* A mutex that exists only long enough to attempt to
         * load this isapi dll, the release this module to all
         * other takers that came along during the one-time
         * load process.  Short lifetime for this lock would
         * be great, however, using r->pool is nasty if those
         * blocked on the lock haven't all unlocked before we
         * attempt to destroy.  A nastier race condition than
         * I want to deal with at this moment...
         */
        apr_thread_rwlock_create(&(*isa)->in_progress, loaded.pool);
        apr_thread_rwlock_wrlock((*isa)->in_progress);
    }

    apr_hash_set(loaded.hash, key, APR_HASH_KEY_STRING, *isa);
    
    /* Now attempt to load the isapi on our own time, 
     * allow other isapi processing to resume.
     */
    apr_thread_mutex_unlock(loaded.lock);

    rv = isapi_load(loaded.pool, s, *isa);
    (*isa)->last_load_time = apr_time_now();
    (*isa)->last_load_rv = rv;

    if (r && (rv == APR_SUCCESS)) {
        /* Let others who are blocked on this particular
         * module resume their requests, for better or worse.
         */
        apr_thread_rwlock_t *unlock = (*isa)->in_progress;
        (*isa)->in_progress = NULL;
        apr_thread_rwlock_unlock(unlock);
    }
    else if (!r && (rv != APR_SUCCESS)) {
        /* We must leave a rwlock around for requests to retry
         * loading this dll after timeup... since we were in 
         * the setup code we had avoided creating this lock.
         */
        apr_thread_rwlock_create(&(*isa)->in_progress, loaded.pool);
    }

    return (*isa)->last_load_rv;
}

/**********************************************************
 *
 *  ISAPI Module request callbacks section
 *
 **********************************************************/

/* Our "Connection ID" structure */
typedef struct isapi_cid {
    EXTENSION_CONTROL_BLOCK *ecb;
    isapi_dir_conf           dconf;
    isapi_loaded            *isa;
    request_rec             *r;
    int                      headers_sent;
    PFN_HSE_IO_COMPLETION    completion;
    void                    *completion_arg;
    apr_thread_mutex_t      *completed;
} isapi_cid;

int APR_THREAD_FUNC GetServerVariable (isapi_cid    *cid, 
                                       char         *variable_name,
                                       void         *buf_data, 
                                       apr_uint32_t *buf_size)
{
    request_rec *r = cid->r;
    const char *result;
    apr_uint32_t len;

    if (!strcmp(variable_name, "ALL_HTTP")) 
    {
        /* lf delimited, colon split, comma seperated and 
         * null terminated list of HTTP_ vars 
         */
        const apr_array_header_t *arr = apr_table_elts(r->subprocess_env);
        const apr_table_entry_t *elts = (const apr_table_entry_t *)arr->elts;
