const char *
uniqueHostname(void)
{
    debugs(21, 3, HERE << " Config: '" << Config.uniqueHostname << "'");
    return Config.uniqueHostname ? Config.uniqueHostname : getMyHostname();
}