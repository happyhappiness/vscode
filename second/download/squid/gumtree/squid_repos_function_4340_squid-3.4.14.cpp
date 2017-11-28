void Ssl::Helper::Init()
{
    assert(ssl_crtd == NULL);

    // we need to start ssl_crtd only if some port(s) need to bump SSL
    bool found = false;
    for (AnyP::PortCfg *s = ::Config.Sockaddr.http; !found && s; s = s->next)
        found = s->flags.tunnelSslBumping;
    for (AnyP::PortCfg *s = ::Config.Sockaddr.https; !found && s; s = s->next)
        found = s->flags.tunnelSslBumping;
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
        char * token = NULL;
        bool db_path_was_found = false;
        bool block_size_was_found = false;
        char buffer[20] = "2048";
        while ((token = strwordtok(NULL, &tmp))) {
            wordlistAdd(&ssl_crtd->cmdline, token);
            if (!strcmp(token, "-b"))
                block_size_was_found = true;
            if (!strcmp(token, "-s")) {
                db_path_was_found = true;
            } else if (db_path_was_found) {
                db_path_was_found = false;
                int fs_block_size = 0;
                storeDirGetBlkSize(token, &fs_block_size);
                snprintf(buffer, sizeof(buffer), "%i", fs_block_size);
            }
        }
        if (!block_size_was_found) {
            wordlistAdd(&ssl_crtd->cmdline, "-b");
            wordlistAdd(&ssl_crtd->cmdline, buffer);
        }
        safe_free(tmp_begin);
    }
    helperOpenServers(ssl_crtd);
}