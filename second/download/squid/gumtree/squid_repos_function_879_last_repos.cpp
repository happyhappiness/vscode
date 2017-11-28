static void
parse_icap_class_type()
{
    debugs(93, DBG_CRITICAL, "WARNING: 'icap_class' is depricated. " <<
           "Use 'adaptation_service_set' instead");
    Adaptation::Config::ParseServiceSet();
}