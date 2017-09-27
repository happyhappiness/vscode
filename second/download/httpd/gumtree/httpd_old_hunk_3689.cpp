        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02817)
                    "could not release lock for cache status");
        }
    }

    ap_rputs("</td></tr>\n</table>\n", r);
    return OK;
}

static void socache_status_register(apr_pool_t *p)
{
    APR_OPTIONAL_HOOK(ap, status_hook, socache_status_hook, NULL, NULL, APR_HOOK_MIDDLE);
