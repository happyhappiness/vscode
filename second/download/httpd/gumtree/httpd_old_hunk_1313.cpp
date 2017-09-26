
        lockname = apr_pstrcat(r->pool, conf->lockpath, dir, "/", lockname, NULL);
    }
    return apr_file_remove(lockname, r->pool);
}

CACHE_DECLARE(int) ap_cache_check_freshness(cache_handle_t *h,
                                            request_rec *r)
{
    apr_status_t status;
    apr_int64_t age, maxage_req, maxage_cresp, maxage, smaxage, maxstale;
    apr_int64_t minfresh;
