static void
parse_UrlHelperTimeout(SquidConfig::UrlHelperTimeout *config)
{
    time_msec_t tval;
    parseTimeLine(&tval, T_SECOND_STR, false, true);
    Config.Timeout.urlRewrite = static_cast<time_t>(tval/1000);

    char *key, *value;
    while(ConfigParser::NextKvPair(key, value)) {
        if (strcasecmp(key, "on_timeout") == 0) {
            if (strcasecmp(value, "bypass") == 0)
                config->action = toutActBypass;
            else if (strcasecmp(value, "fail") == 0)
                config->action = toutActFail;
            else if (strcasecmp(value, "retry") == 0)
                config->action = toutActRetry;
            else if (strcasecmp(value, "use_configured_response") == 0) {
                config->action = toutActUseConfiguredResponse;
            } else {
                debugs(3, DBG_CRITICAL, "FATAL: unsuported \"on_timeout\"  action:" << value);
                self_destruct();
                return;
            }
        } else if (strcasecmp(key, "response") == 0) {
            config->response = xstrdup(value);
        } else {
            debugs(3, DBG_CRITICAL, "FATAL: unsuported option " << key);
            self_destruct();
            return;
        }
    }

    if (config->action == toutActUseConfiguredResponse && !config->response) {
        debugs(3, DBG_CRITICAL, "FATAL: Expected 'response=' option after 'on_timeout=use_configured_response' option");
        self_destruct();
    }

    if (config->action != toutActUseConfiguredResponse && config->response) {
        debugs(3, DBG_CRITICAL, "FATAL: 'response=' option is valid only when used with the  'on_timeout=use_configured_response' option");
        self_destruct();
    }
}