                int len;

                len = strlen(current->right->token.value);

                if (current->right->token.value[len - 1] == '/') {

                    current->right->token.value[len - 1] = '\0';

                }

                else {

                    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

                                "Invalid rexp \"%s\" in file %s",

                                current->right->token.value, r->filename);

                    ap_rputs(error, r);

                    goto RETURN;

                }

#ifdef DEBUG_INCLUDE

