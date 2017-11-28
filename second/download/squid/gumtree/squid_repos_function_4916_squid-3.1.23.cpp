bool
AuthNTLMConfig::configured() const
{
    if ((authenticate != NULL) && (authenticateChildren != 0)) {
        debugs(29, 9, "AuthNTLMConfig::configured: returning configured");
        return true;
    }

    debugs(29, 9, "AuthNTLMConfig::configured: returning unconfigured");
    return false;
}