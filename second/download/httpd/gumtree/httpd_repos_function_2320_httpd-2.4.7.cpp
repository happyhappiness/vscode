static const char *set_reqtimeout_param(reqtimeout_srv_cfg *conf,
                                      apr_pool_t *p,
                                      const char *key,
                                      const char *val)
{
    const char *ret = NULL;
    char *rate_str = NULL, *initial_str, *max_str = NULL;
    int rate = 0, initial = 0, max = 0;
    enum { PARAM_HEADER, PARAM_BODY } type;

    if (!strcasecmp(key, "header")) {
        type = PARAM_HEADER;
    }
    else if (!strcasecmp(key, "body")) {
        type = PARAM_BODY;
    }
    else {
        return "Unknown RequestReadTimeout parameter";
    }

    if ((rate_str = ap_strcasestr(val, ",minrate="))) {
        initial_str = apr_pstrndup(p, val, rate_str - val);
        rate_str += strlen(",minrate=");
        ret = parse_int(p, rate_str, &rate);
        if (ret)
            return ret;

        if (rate == 0)
            return "Minimum data rate must be larger than 0";

        if ((max_str = strchr(initial_str, '-'))) {
            *max_str++ = '\0';
            ret = parse_int(p, max_str, &max);
            if (ret)
                return ret;
        }

        ret = parse_int(p, initial_str, &initial);
    }
    else {
        if (ap_strchr_c(val, '-'))
            return "Must set MinRate option if using timeout range";
        ret = parse_int(p, val, &initial);
    }

    if (ret)
        return ret;

    if (max && initial >= max) {
        return "Maximum timeout must be larger than initial timeout";
    }

    if (type == PARAM_HEADER) {
        conf->header_timeout = initial;
        conf->header_max_timeout = max;
        conf->header_min_rate = rate;
        if (rate)
            conf->header_rate_factor = apr_time_from_sec(1) / rate;
    }
    else {
        conf->body_timeout = initial;
        conf->body_max_timeout = max;
        conf->body_min_rate = rate;
        if (rate)
            conf->body_rate_factor = apr_time_from_sec(1) / rate;
    }
    return ret;
}