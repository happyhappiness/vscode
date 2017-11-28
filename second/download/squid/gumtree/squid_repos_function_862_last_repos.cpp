void
configFreeMemory(void)
{
    free_all();
    Config.ssl_client.sslContext.reset();
#if USE_OPENSSL
    Ssl::unloadSquidUntrusted();
#endif
}