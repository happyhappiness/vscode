ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                                "Invalid rexp \"%s\" in file %s",
                                current->right->token.value, r->filename);