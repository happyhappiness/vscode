bool
AuthNegotiateConfig::configured() const
{
    if ((authenticate != NULL) && (authenticateChildren != 0)) {
        debugs(29, 9, "AuthNegotiateConfig::configured: returning configured");
        return true;
    }

    debugs(29, 9, "AuthNegotiateConfig::configured: returning unconfigured");
    return false;
}