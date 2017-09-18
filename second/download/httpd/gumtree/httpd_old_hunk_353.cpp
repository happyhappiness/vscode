          || sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE) {
        char *prompt;
        int i;

        if (sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE) {
            if (!readtty) {
                ssl_log(s, SSL_LOG_INFO,
                        "Init: Creating pass phrase dialog pipe child '%s'",
                        sc->server->pphrase_dialog_path);
	        if (ssl_pipe_child_create(p, sc->server->pphrase_dialog_path)
                        != APR_SUCCESS) {
                    ssl_log(s, SSL_LOG_ERROR,
                            "Init: Failed to create pass phrase pipe '%s'",
                            sc->server->pphrase_dialog_path);
                    PEMerr(PEM_F_DEF_CALLBACK,PEM_R_PROBLEMS_GETTING_PASSWORD);
                    memset(buf, 0, (unsigned int)bufsize);
                    return (-1);
                }
            }
            ssl_log(s, SSL_LOG_INFO,
                    "Init: Requesting pass phrase via piped dialog");
        }
        else { /* sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN */ 
#ifdef WIN32
            PEMerr(PEM_F_DEF_CALLBACK,PEM_R_PROBLEMS_GETTING_PASSWORD);
            memset(buf, 0, (unsigned int)bufsize);
            return (-1);
