                     return (-1);
                 }
             }
             ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                          "Init: Requesting pass phrase via piped dialog");
         }
-        else { /* sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN */ 
+        else { /* sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN */
 #ifdef WIN32
             PEMerr(PEM_F_DEF_CALLBACK,PEM_R_PROBLEMS_GETTING_PASSWORD);
             memset(buf, 0, (unsigned int)bufsize);
             return (-1);
 #else
             /*
