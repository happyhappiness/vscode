#include "apr_lib.h"
#include "util_filter.h"
#include "http_request.h"

#include <ctype.h>

static const char s_szCaseFilterName[]="CaseFilter";
module AP_MODULE_DECLARE_DATA case_filter_module;

typedef struct
    {
    int bEnabled;
    } CaseFilterConfig;

static void *CaseFilterCreateServerConfig(apr_pool_t *p,server_rec *s)
    {
    CaseFilterConfig *pConfig=apr_pcalloc(p,sizeof *pConfig);

    pConfig->bEnabled=0;

    return pConfig;
    }

static void CaseFilterInsertFilter(request_rec *r)
    {
    CaseFilterConfig *pConfig=ap_get_module_config(r->server->module_config,
                                                   &case_filter_module);

    if(!pConfig->bEnabled)
        return;

    ap_add_output_filter(s_szCaseFilterName,NULL,r,r->connection);
    }

static apr_status_t CaseFilterOutFilter(ap_filter_t *f,
                                        apr_bucket_brigade *pbbIn)
    {
    request_rec *r = f->r;
    conn_rec *c = r->connection;
    apr_bucket *pbktIn;
    apr_bucket_brigade *pbbOut;

    pbbOut=apr_brigade_create(r->pool, c->bucket_alloc);
    for (pbktIn = APR_BRIGADE_FIRST(pbbIn);
         pbktIn != APR_BRIGADE_SENTINEL(pbbIn);
         pbktIn = APR_BUCKET_NEXT(pbktIn))
    {
        const char *data;
        apr_size_t len;
        char *buf;
        apr_size_t n;
        apr_bucket *pbktOut;

        if(APR_BUCKET_IS_EOS(pbktIn))
            {
            apr_bucket *pbktEOS=apr_bucket_eos_create(c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(pbbOut,pbktEOS);
            continue;
            }

        /* read */
        apr_bucket_read(pbktIn,&data,&len,APR_BLOCK_READ);

        /* write */
        buf = apr_bucket_alloc(len, c->bucket_alloc);
        for(n=0 ; n < len ; ++n)
            buf[n] = apr_toupper(data[n]);

        pbktOut = apr_bucket_heap_create(buf, len, apr_bucket_free,
                                         c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(pbbOut,pbktOut);
        }

    /* Q: is there any advantage to passing a brigade for each bucket?
     * A: obviously, it can cut down server resource consumption, if this
     * experimental module was fed a file of 4MB, it would be using 8MB for
     * the 'read' buckets and the 'write' buckets.
     *
     * Note it is more efficient to consume (destroy) each bucket as it's
     * processed above than to do a single cleanup down here.  In any case,
     * don't let our caller pass the same buckets to us, twice;
     */
    apr_brigade_cleanup(pbbIn);
    return ap_pass_brigade(f->next,pbbOut);
    }

static const char *CaseFilterEnable(cmd_parms *cmd, void *dummy, int arg)
    {
    CaseFilterConfig *pConfig=ap_get_module_config(cmd->server->module_config,
                                                   &case_filter_module);
    pConfig->bEnabled=arg;

    return NULL;
    }

static const command_rec CaseFilterCmds[] =
    {
    AP_INIT_FLAG("CaseFilter", CaseFilterEnable, NULL, RSRC_CONF,
                 "Run a case filter on this host"),
    { NULL }
    };

static void CaseFilterRegisterHooks(apr_pool_t *p)
    {
    ap_hook_insert_filter(CaseFilterInsertFilter,NULL,NULL,APR_HOOK_MIDDLE);
    ap_register_output_filter(s_szCaseFilterName,CaseFilterOutFilter,NULL,
                              AP_FTYPE_RESOURCE);
    }

AP_DECLARE_MODULE(case_filter) =
{
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
