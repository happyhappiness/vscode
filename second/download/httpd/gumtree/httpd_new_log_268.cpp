ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                                "Invalid rexp \"%s\" in file %s",
                                current->right->token.value, r->filename);