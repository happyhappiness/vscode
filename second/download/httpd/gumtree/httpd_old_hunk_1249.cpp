    resident_time = now - info->response_time;
    current_age = corrected_initial_age + resident_time;

    return apr_time_sec(current_age);
}

CACHE_DECLARE(int) ap_cache_check_freshness(cache_handle_t *h,
                                            request_rec *r)
{
    apr_int64_t age, maxage_req, maxage_cresp, maxage, smaxage, maxstale;
    apr_int64_t minfresh;
    const char *cc_cresp, *cc_req;
    const char *pragma;
    const char *agestr = NULL;
    const char *expstr = NULL;
    char *val;
    apr_time_t age_c = 0;
    cache_info *info = &(h->cache_obj->info);
    cache_server_conf *conf =
      (cache_server_conf *)ap_get_module_config(r->server->module_config,
                                                &cache_module);

    /*
     * We now want to check if our cached data is still fresh. This depends
