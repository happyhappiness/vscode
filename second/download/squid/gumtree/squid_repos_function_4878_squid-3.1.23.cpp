bool
AuthBasicConfig::configured() const
{
    if ((authenticate != NULL) && (authenticateChildren != 0) &&
            (basicAuthRealm != NULL)) {
        debugs(29, 9, HERE << "returning configured");
        return true;
    }

    debugs(29, 9, HERE << "returning unconfigured");
    return false;
}