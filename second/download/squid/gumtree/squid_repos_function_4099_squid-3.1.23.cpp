void Ssl::Helper::Shutdown()
{
    if (!ssl_crtd)
        return;
    helperShutdown(ssl_crtd);
    wordlistDestroy(&ssl_crtd->cmdline);
    if (!shutting_down)
        return;
    helperFree(ssl_crtd);
    ssl_crtd = NULL;
}