void
configFreeMemory(void)
{
    free_all();
#if USE_SSL
    SSL_CTX_free(Config.ssl_client.sslContext);
#endif
}