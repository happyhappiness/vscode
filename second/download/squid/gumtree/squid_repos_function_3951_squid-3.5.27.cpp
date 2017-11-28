bool
Adaptation::ServiceConfig::grokExtension(const char *name, const char *value)
{
    // we do not accept extensions by default
    debugs(3, DBG_CRITICAL, cfg_filename << ':' << config_lineno << ": " <<
           "ERROR: unknown adaptation service option: " <<
           name << '=' << value);
    return false;
}