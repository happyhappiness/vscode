static void
gnutlsDebugHandler(int level, const char *msg)
{
    debugVerbose(level, "GnuTLS: " << msg);
}