void
configFreeMemory(void)
{
    free_all();
#if USE_OPENSSL
    SSL_CTX_free(Config.ssl_client.sslContext);
    Ssl::unloadSquidUntrusted();
#endif
}