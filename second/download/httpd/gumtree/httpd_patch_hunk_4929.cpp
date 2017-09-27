     }
 
     fprintf(stderr, "Total #records : %d\n", i);
     return APR_SUCCESS;
 }
 
-static void to64(char *s, unsigned long v, int n)
-{
-    static unsigned char itoa64[] =         /* 0 ... 63 => ASCII - 64 */
-    "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
-
-    while (--n >= 0) {
-        *s++ = itoa64[v&0x3f];
-        v >>= 6;
-    }
-}
-
-static apr_status_t htdbm_make(htdbm_t *htdbm)
+static int htdbm_make(htdbm_t *htdbm)
 {
     char cpw[MAX_STRING_LEN];
-    char salt[9];
-#if (!(defined(WIN32) || defined(NETWARE)))
-    char *cbuf;
-#endif
+    int ret;
 
-    switch (htdbm->alg) {
-        case ALG_APSHA:
-            /* XXX cpw >= 28 + strlen(sha1) chars - fixed len SHA */
-            apr_sha1_base64(htdbm->userpass,strlen(htdbm->userpass),cpw);
-        break;
-
-        case ALG_APMD5:
-            (void) srand((int) time((time_t *) NULL));
-            to64(&salt[0], rand(), 8);
-            salt[8] = '\0';
-            apr_md5_encode((const char *)htdbm->userpass, (const char *)salt,
-                            cpw, sizeof(cpw));
-        break;
-        case ALG_PLAIN:
-            /* XXX this len limitation is not in sync with any HTTPd len. */
-            apr_cpystrn(cpw,htdbm->userpass,sizeof(cpw));
-#if (!(defined(WIN32) || defined(NETWARE)))
-            fprintf(stderr, "Warning: Plain text passwords aren't supported by the "
-                    "server on this platform!\n");
-#endif
-        break;
-#if (!(defined(WIN32) || defined(NETWARE)))
-        case ALG_CRYPT:
-            (void) srand((int) time((time_t *) NULL));
-            to64(&salt[0], rand(), 8);
-            salt[8] = '\0';
-            cbuf = crypt(htdbm->userpass, salt);
-            if (cbuf == NULL) {
-                char errbuf[128];
-                
-                fprintf(stderr, "crypt() failed: %s\n", 
-                        apr_strerror(errno, errbuf, sizeof errbuf));
-                exit(ERR_PWMISMATCH);
-            }
-            apr_cpystrn(cpw, cbuf, sizeof(cpw) - 1);
-            fprintf(stderr, "CRYPT is now deprecated, use MD5 instead!\n");
-#endif
-        default:
-        break;
+    htdbm->ctx.out = cpw;
+    htdbm->ctx.out_len = sizeof(cpw);
+    ret = mkhash(&htdbm->ctx);
+    if (ret != 0) {
+        fprintf(stderr, "Error: %s\n", htdbm->ctx.errstr);
+        return ret;
     }
-    htdbm->userpass = apr_pstrdup(htdbm->pool, cpw);
-    return APR_SUCCESS;
+    htdbm->ctx.passwd = apr_pstrdup(htdbm->ctx.pool, cpw);
+    return 0;
 }
 
 static apr_status_t htdbm_valid_username(htdbm_t *htdbm)
 {
     if (!htdbm->username || (strlen(htdbm->username) > 64) || (strlen(htdbm->username) < 1)) {
         fprintf(stderr, "Invalid username length\n");
