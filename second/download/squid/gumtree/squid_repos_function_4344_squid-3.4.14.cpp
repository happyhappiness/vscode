void Ssl::CertValidationHelper::Init()
{
    assert(ssl_crt_validator == NULL);

    // we need to start ssl_crtd only if some port(s) need to bump SSL
    bool found = false;
    for (AnyP::PortCfg *s = ::Config.Sockaddr.http; !found && s; s = s->next)
        found = s->flags.tunnelSslBumping;
    for (AnyP::PortCfg *s = ::Config.Sockaddr.https; !found && s; s = s->next)
        found = s->flags.tunnelSslBumping;
    if (!found)
        return;

    ssl_crt_validator = new helper("ssl_crt_validator");
    ssl_crt_validator->childs.updateLimits(Ssl::TheConfig.ssl_crt_validator_Children);
    ssl_crt_validator->ipc_type = IPC_STREAM;
    // The crtd messages may contain the eol ('\n') character. We are
    // going to use the '\1' char as the end-of-message mark.
    ssl_crt_validator->eom = '\1';
    assert(ssl_crt_validator->cmdline == NULL);

    int ttl = 60;
    size_t cache = 2048;
    {
        char *tmp = xstrdup(Ssl::TheConfig.ssl_crt_validator);
        char *tmp_begin = tmp;
        char * token = NULL;
        bool parseParams = true;
        while ((token = strwordtok(NULL, &tmp))) {
            if (parseParams) {
                if (strncmp(token, "ttl=", 4) == 0) {
                    ttl = atoi(token + 4);
                    continue;
                } else if (strncmp(token, "cache=", 6) == 0) {
                    cache = atoi(token + 6);
                    continue;
                } else
                    parseParams = false;
            }
            wordlistAdd(&ssl_crt_validator->cmdline, token);
        }
        xfree(tmp_begin);
    }
    helperOpenServers(ssl_crt_validator);

    //WARNING: initializing static member in an object initialization method
    assert(HelperCache == NULL);
    HelperCache = new LruMap<Ssl::CertValidationResponse>(ttl, cache);
}