bool
Adaptation::ServiceConfig::grokLong(long &var, const char *name, const char *value)
{
    char *bad = NULL;
    const long p = strtol(value, &bad, 0);
    if (p < 0 || bad == value) {
        debugs(3, DBG_CRITICAL, "ERROR: " << cfg_filename << ':' <<
               config_lineno << ": " << "wrong value for " << name << "; " <<
               "a non-negative integer expected but got: " << value);
        return false;
    }
    var = p;
    return true;
}