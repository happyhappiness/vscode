                              "'%s'", sc->server->pphrase_dialog_path);
                 if (ssl_pipe_child_create(p, sc->server->pphrase_dialog_path)
                         != APR_SUCCESS) {
                     ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01966)
                                  "Init: Failed to create pass phrase pipe '%s'",
                                  sc->server->pphrase_dialog_path);
-                    PEMerr(PEM_F_DEF_CALLBACK,PEM_R_PROBLEMS_GETTING_PASSWORD);
+                    PEMerr(PEM_F_PEM_DEF_CALLBACK,PEM_R_PROBLEMS_GETTING_PASSWORD);
                     memset(buf, 0, (unsigned int)bufsize);
                     return (-1);
                 }
             }
             ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01967)
                          "Init: Requesting pass phrase via piped dialog");
         }
         else { /* sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN */
 #ifdef WIN32
-            PEMerr(PEM_F_DEF_CALLBACK,PEM_R_PROBLEMS_GETTING_PASSWORD);
+            PEMerr(PEM_F_PEM_DEF_CALLBACK,PEM_R_PROBLEMS_GETTING_PASSWORD);
             memset(buf, 0, (unsigned int)bufsize);
             return (-1);
 #else
             /*
              * stderr has already been redirected to the error_log.
              * rather than attempting to temporarily rehook it to the terminal,
