bool
Adaptation::ServiceConfig::grokOnOverload(SrvBehaviour &var, const char *value)
{
    if (strcmp(value, "block") == 0)
        var = srvBlock;
    else if (strcmp(value, "bypass") == 0)
        var = srvBypass;
    else if (strcmp(value, "wait") == 0)
        var = srvWait;
    else if (strcmp(value, "force") == 0)
        var = srvForce;
    else {
        debugs(3, DBG_CRITICAL, "ERROR: " << cfg_filename << ':' <<
               config_lineno << ": " << "wrong value for on-overload; " <<
               "'block', 'bypass', 'wait' or 'force' expected but got: " << value);
        return false;
    }
    return true;
}