             exit(ERR_OVERFLOW);
         }
         if (strcmp(pwi, pwc) != 0) {
             fprintf(stderr, "Password verification error\n");
             exit(ERR_PWMISMATCH);
         }
-            
+
         h->userpass = apr_pstrdup(pool,  pwi);
     }
     if (need_cmnt && pwd_supplied)
         h->comment = apr_pstrdup(pool, argv[i+3]);
     else if (need_cmnt)
         h->comment = apr_pstrdup(pool, argv[i+2]);
