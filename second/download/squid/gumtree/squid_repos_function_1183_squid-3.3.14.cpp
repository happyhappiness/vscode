static void
free_icap_service_type(Adaptation::Icap::Config * cfg)
{
    cfg->freeService();
}