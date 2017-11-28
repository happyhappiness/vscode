void Ssl::Helper::Init()
{
    if (ssl_crtd == NULL)
        ssl_crtd = helperCreate("ssl_crtd");
    ssl_crtd->n_to_start = Ssl::TheConfig.ssl_crtd_n_running;
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