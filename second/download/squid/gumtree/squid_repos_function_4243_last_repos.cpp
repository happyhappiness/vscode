void
ACLAdaptationServiceData::parse()
{
    Adaptation::Config::needHistory = true;
    while (char *t = ConfigParser::strtokFile()) {
        if (
#if USE_ECAP
            Adaptation::Ecap::TheConfig.findServiceConfig(t) == NULL &&
#endif
#if ICAP_CLIENT
            Adaptation::Icap::TheConfig.findServiceConfig(t) == NULL &&
#endif
            Adaptation::FindGroup(t) == NULL) {
            debugs(28, DBG_CRITICAL, "FATAL: Adaptation service/group " << t << " in adaptation_service acl is not defined");
            self_destruct();
        }
        insert(t);
    }
}