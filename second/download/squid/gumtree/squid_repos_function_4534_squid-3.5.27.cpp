void Ssl::Helper::Init()
{
    assert(ssl_crtd == NULL);

    // we need to start ssl_crtd only if some port(s) need to bump SSL *and* generate certificates
    // TODO: generate host certificates for SNI enabled accel ports
    bool found = false;
    for (AnyP::PortCfgPointer s = HttpPortList; !found && s != NULL; s = s->next)
        found = s->flags.tunnelSslBumping && s->generateHostCertificates;
    for (AnyP::PortCfgPointer s = HttpsPortList; !found && s != NULL; s = s->next)
        found = s->flags.tunnelSslBumping && s->generateHostCertificates;
    if (!found)
        return;

    ssl_crtd = new helper("ssl_crtd");
    ssl_crtd->childs.updateLimits(Ssl::TheConfig.ssl_crtdChildren);
    ssl_crtd->ipc_type = IPC_STREAM;
    // The crtd messages may contain the eol ('\n') character. We are
    // going to use the '\1' char as the end-of-message mark.
    ssl_crtd->eom = '\1';
    assert(ssl_crtd->cmdline == NULL);
    {
        char *tmp = xstrdup(Ssl::TheConfig.ssl_crtd);
        char *tmp_begin = tmp;
        char *token = NULL;
        while ((token = strwordtok(NULL, &tmp))) {
            wordlistAdd(&ssl_crtd->cmdline, token);
        }
        safe_free(tmp_begin);
    }
    helperOpenServers(ssl_crtd);
}