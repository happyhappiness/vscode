static void free_icap_service_failure_limit(Adaptation::Icap::Config *cfg)
{
    cfg->oldest_service_failure = 0;
    cfg->service_failure_limit = 0;
}