                i = pipe_get_passwd_cb(buf, bufsize, "", FALSE);
            }
            else { /* sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN */
                i = EVP_read_pw_string(buf, bufsize, "", FALSE);
            }
            if (i != 0) {
                PEMerr(PEM_F_PEM_DEF_CALLBACK,PEM_R_PROBLEMS_GETTING_PASSWORD);
                memset(buf, 0, (unsigned int)bufsize);
                return (-1);
            }
            len = strlen(buf);
            if (len < 1)
                apr_file_printf(writetty, "Apache:mod_ssl:Error: Pass phrase empty (needs to be at least 1 character).\n");
