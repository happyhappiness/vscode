dump_ecap_service_type(StoreEntry * entry, const char *name, const Adaptation::Ecap::Config &cfg)
{
    cfg.dumpService(entry, name);
}

#endif /* USE_ECAP */

#if ICAP_CLIENT
static void parse_icap_service_failure_limit(Adaptation::Icap::Config *cfg)
{
    char *token;
    time_t d;
    time_t m;
    cfg->service_failure_limit = GetInteger();

    if ((token = strtok(NULL, w_space)) == NULL)
        return;

    if (strcmp(token,"in") != 0) {
        debugs(3, 0, "expecting 'in' on'"  << config_input_line << "'");
        self_destruct();
    }

    if ((token = strtok(NULL, w_space)) == NULL) {
        self_destruct();
    }

    d = static_cast<time_t> (xatoi(token));

    m = static_cast<time_t> (1);

    if (0 == d)
        (void) 0;
    else if ((token = strtok(NULL, w_space)) == NULL) {
        debugs(3, 0, "No time-units on '" << config_input_line << "'");
        self_destruct();
    } else if ((m = parseTimeUnits(token, false)) == 0)
        self_destruct();

    cfg->oldest_service_failure = (m * d);
}

static void dump_icap_service_failure_limit(StoreEntry *entry, const char *name, const Adaptation::Icap::Config &cfg)
{
    storeAppendPrintf(entry, "%s %d", name, cfg.service_failure_limit);
    if (cfg.oldest_service_failure > 0) {
        storeAppendPrintf(entry, " in %d seconds", (int)cfg.oldest_service_failure);
    }
    storeAppendPrintf(entry, "\n");
}

static void free_icap_service_failure_limit(Adaptation::Icap::Config *cfg)
{
    cfg->oldest_service_failure = 0;
    cfg->service_failure_limit = 0;
}

#endif
