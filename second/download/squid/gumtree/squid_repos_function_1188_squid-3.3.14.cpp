static void
free_ecap_service_type(Adaptation::Ecap::Config * cfg)
{
    cfg->freeService();
}