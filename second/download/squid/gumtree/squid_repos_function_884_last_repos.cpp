static void parse_icap_service_failure_limit(Adaptation::Icap::Config *cfg)
{
    char *token;
    time_t d;
    time_t m;
    cfg->service_failure_limit = GetInteger();

    if ((token = ConfigParser::NextToken()) == NULL)
        return;

    if (strcmp(token,"in") != 0) {
        debugs(3, DBG_CRITICAL, "expecting 'in' on'"  << config_input_line << "'");
        self_destruct();
        return;
    }

    if ((token = ConfigParser::NextToken()) == NULL) {
        self_destruct();
        return;
    }

    d = static_cast<time_t> (xatoi(token));

    m = static_cast<time_t> (1);

    if (0 == d)
        (void) 0;
    else if ((token = ConfigParser::NextToken()) == NULL) {
        debugs(3, DBG_CRITICAL, "No time-units on '" << config_input_line << "'");
        self_destruct();
        return;
    } else if ((m = parseTimeUnits(token, false)) == 0) {
        self_destruct();
        return;
    }

    cfg->oldest_service_failure = (m * d);
}