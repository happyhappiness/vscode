             ret = ERR_PWMISMATCH;
             break;
         }
 
         apr_cpystrn(ctx->out, cbuf, ctx->out_len - 1);
         if (strlen(pw) > 8) {
-            char *truncpw = strdup(pw);
+            char *truncpw = apr_pstrdup(ctx->pool, pw);
             truncpw[8] = '\0';
             if (!strcmp(ctx->out, crypt(truncpw, salt))) {
                 apr_file_printf(errfile, "Warning: Password truncated to 8 "
                                 "characters by CRYPT algorithm." NL);
             }
             memset(truncpw, '\0', strlen(pw));
-            free(truncpw);
         }
         break;
 #endif /* CRYPT_ALGO_SUPPORTED */
 
 #if BCRYPT_ALGO_SUPPORTED
     case ALG_BCRYPT:
