bool
Adaptation::ServiceConfig::grokBool(bool &var, const char *name, const char *value)
{
    if (!strcmp(value, "0") || !strcmp(value, "off"))
        var = false;
    else if (!strcmp(value, "1") || !strcmp(value, "on"))
        var = true;
    else {
        debugs(3, 0, HERE << cfg_filename << ':' << config_lineno << ": " <<
               "wrong value for boolean " << name << "; " <<
               "'0', '1', 'on', or 'off' expected but got: " << value);
        return false;
    }

    return true;
}