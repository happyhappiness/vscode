             apr_md5_encode((const char *)htdbm->userpass, (const char *)salt,
                             cpw, sizeof(cpw));
         break;
         case ALG_PLAIN:
             /* XXX this len limitation is not in sync with any HTTPd len. */
             apr_cpystrn(cpw,htdbm->userpass,sizeof(cpw));
-#if APR_HAVE_CRYPT_H
+#if (!(defined(WIN32) || defined(TPF) || defined(NETWARE)))
             fprintf(stderr, "Warning: Plain text passwords aren't supported by the "
                     "server on this platform!\n");
 #endif
         break;
-#if APR_HAVE_CRYPT_H
+#if (!(defined(WIN32) || defined(TPF) || defined(NETWARE)))
         case ALG_CRYPT:
             (void) srand((int) time((time_t *) NULL));
             to64(&salt[0], rand(), 8);
             salt[8] = '\0';
             apr_cpystrn(cpw, (char *)crypt(htdbm->userpass, salt), sizeof(cpw) - 1);
             fprintf(stderr, "CRYPT is now deprecated, use MD5 instead!\n");
