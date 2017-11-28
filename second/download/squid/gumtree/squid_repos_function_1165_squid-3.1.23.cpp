static void
parse_icap_access_type()
{
    debugs(93, 0, "WARNING: 'icap_access' is depricated. " <<
           "Use 'adaptation_access' instead");
    Adaptation::Config::ParseAccess(LegacyParser);
}