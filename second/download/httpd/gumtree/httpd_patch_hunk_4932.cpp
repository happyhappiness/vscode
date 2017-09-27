 
 #ifdef WIN32
 #include <conio.h>
 #define unlink _unlink
 #endif
 
-#if !APR_CHARSET_EBCDIC
-#define LF 10
-#define CR 13
-#else /*APR_CHARSET_EBCDIC*/
-#define LF '\n'
-#define CR '\r'
-#endif /*APR_CHARSET_EBCDIC*/
-
-#define MAX_STRING_LEN 256
-#define ALG_PLAIN 0
-#define ALG_CRYPT 1
-#define ALG_APMD5 2
-#define ALG_APSHA 3
-
-#define ERR_FILEPERM 1
-#define ERR_SYNTAX 2
-#define ERR_PWMISMATCH 3
-#define ERR_INTERRUPTED 4
-#define ERR_OVERFLOW 5
-#define ERR_BADUSER 6
-#define ERR_INVALID 7
-
 #define APHTP_NEWFILE        1
 #define APHTP_NOFILE         2
-#define APHTP_NONINTERACTIVE 4
-#define APHTP_DELUSER        8
+#define APHTP_DELUSER        4
 
-apr_file_t *errfile;
 apr_file_t *ftemp = NULL;
 
-#define NL APR_EOL_STR
-
-#if defined(WIN32) || defined(NETWARE)
-#define CRYPT_ALGO_SUPPORTED 0
-#else
-#define CRYPT_ALGO_SUPPORTED 1
-#endif
-
-#if CRYPT_ALGO_SUPPORTED
-static void to64(char *s, unsigned long v, int n)
-{
-    static unsigned char itoa64[] =         /* 0 ... 63 => ASCII - 64 */
-        "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
-
-    while (--n >= 0) {
-        *s++ = itoa64[v&0x3f];
-        v >>= 6;
-    }
-}
-#endif
-
-static void generate_salt(char *s, size_t size)
-{
-    static unsigned char tbl[] =
-        "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
-    size_t i;
-    for (i = 0; i < size; ++i) {
-        int idx = (int) (64.0 * rand() / (RAND_MAX + 1.0));
-        s[i] = tbl[idx];
-    }
-}
-
-static apr_status_t seed_rand(void)
+static int mkrecord(struct passwd_ctx *ctx, char *user)
 {
-    int seed = 0;
-    apr_status_t rv;
-    rv = apr_generate_random_bytes((unsigned char*) &seed, sizeof(seed));
-    if (rv) {
-        apr_file_printf(errfile, "Unable to generate random bytes: %pm" NL, &rv);
-        return rv;
-    }
-    srand(seed);
-    return rv;
-}
-
-static void putline(apr_file_t *f, const char *l)
-{
-    apr_status_t rc;
-    rc = apr_file_puts(l, f);
-    if (rc != APR_SUCCESS) {
-        char errstr[MAX_STRING_LEN];
-        apr_strerror(rc, errstr, MAX_STRING_LEN);
-        apr_file_printf(errfile, "Error writing temp file: %s" NL, errstr);
-        apr_file_close(f);
-        exit(ERR_FILEPERM);
-    }
-}
-
-/*
- * Make a password record from the given information.  A zero return
- * indicates success; failure means that the output buffer contains an
- * error message instead.
- */
-static int mkrecord(char *user, char *record, apr_size_t rlen, char *passwd,
-                    int alg)
-{
-    char *pw;
-    char cpw[120];
-    char pwin[MAX_STRING_LEN];
-    char pwv[MAX_STRING_LEN];
-    char salt[9];
-    apr_size_t bufsize;
-#if CRYPT_ALGO_SUPPORTED
-    char *cbuf;
-#endif
-
-    if (passwd != NULL) {
-        pw = passwd;
-    }
-    else {
-        bufsize = sizeof(pwin);
-        if (apr_password_get("New password: ", pwin, &bufsize) != 0) {
-            apr_snprintf(record, (rlen - 1), "password too long (>%"
-                         APR_SIZE_T_FMT ")", sizeof(pwin) - 1);
-            return ERR_OVERFLOW;
-        }
-        bufsize = sizeof(pwv);
-        apr_password_get("Re-type new password: ", pwv, &bufsize);
-        if (strcmp(pwin, pwv) != 0) {
-            apr_cpystrn(record, "password verification error", (rlen - 1));
-            return ERR_PWMISMATCH;
-        }
-        pw = pwin;
-        memset(pwv, '\0', sizeof(pwin));
-    }
-    switch (alg) {
-
-    case ALG_APSHA:
-        /* XXX cpw >= 28 + strlen(sha1) chars - fixed len SHA */
-        apr_sha1_base64(pw,strlen(pw),cpw);
-        break;
-
-    case ALG_APMD5:
-        if (seed_rand()) {
-            break;
-        }
-        generate_salt(&salt[0], 8);
-        salt[8] = '\0';
-
-        apr_md5_encode((const char *)pw, (const char *)salt,
-                     cpw, sizeof(cpw));
-        break;
-
-    case ALG_PLAIN:
-        /* XXX this len limitation is not in sync with any HTTPd len. */
-        apr_cpystrn(cpw,pw,sizeof(cpw));
-        break;
-
-#if CRYPT_ALGO_SUPPORTED
-    case ALG_CRYPT:
-    default:
-        if (seed_rand()) {
-            break;
-        }
-        to64(&salt[0], rand(), 8);
-        salt[8] = '\0';
-
-        cbuf = crypt(pw, salt);
-        if (cbuf == NULL) {
-            char errbuf[128];
-
-            apr_snprintf(record, rlen-1, "crypt() failed: %s", 
-                         apr_strerror(errno, errbuf, sizeof errbuf));
-            return ERR_PWMISMATCH;
-        }
-
-        apr_cpystrn(cpw, cbuf, sizeof(cpw) - 1);
-        if (strlen(pw) > 8) {
-            char *truncpw = strdup(pw);
-            truncpw[8] = '\0';
-            if (!strcmp(cpw, crypt(truncpw, salt))) {
-                apr_file_printf(errfile, "Warning: Password truncated to 8 characters "
-                                "by CRYPT algorithm." NL);
-            }
-            free(truncpw);
-        }
-        break;
-#endif /* CRYPT_ALGO_SUPPORTED */
-    }
-    memset(pw, '\0', strlen(pw));
-
-    /*
-     * Check to see if the buffer is large enough to hold the username,
-     * hash, and delimiters.
-     */
-    if ((strlen(user) + 1 + strlen(cpw)) > (rlen - 1)) {
-        apr_cpystrn(record, "resultant record too long", (rlen - 1));
+    char hash_str[MAX_STRING_LEN];
+    int ret;
+    ctx->out = hash_str;
+    ctx->out_len = sizeof(hash_str);
+
+    ret = mkhash(ctx);
+    if (ret)
+        return ret;
+
+    ctx->out = apr_pstrcat(ctx->pool, user, ":", hash_str, NL, NULL);
+    if (strlen(ctx->out) >= MAX_STRING_LEN) {
+        ctx->errstr = "resultant record too long";
         return ERR_OVERFLOW;
     }
-    strcpy(record, user);
-    strcat(record, ":");
-    strcat(record, cpw);
-    strcat(record, "\n");
     return 0;
 }
 
 static void usage(void)
 {
-    apr_file_printf(errfile, "Usage:" NL);
-    apr_file_printf(errfile, "\thtpasswd [-cmdpsD] passwordfile username" NL);
-    apr_file_printf(errfile, "\thtpasswd -b[cmdpsD] passwordfile username "
-                    "password" NL NL);
-    apr_file_printf(errfile, "\thtpasswd -n[mdps] username" NL);
-    apr_file_printf(errfile, "\thtpasswd -nb[mdps] username password" NL);
-    apr_file_printf(errfile, " -c  Create a new file." NL);
-    apr_file_printf(errfile, " -n  Don't update file; display results on "
-                    "stdout." NL);
-    apr_file_printf(errfile, " -m  Force MD5 encryption of the password"
-        " (default)"
-        "." NL);
-    apr_file_printf(errfile, " -d  Force CRYPT encryption of the password"
-            " (8 chars max, insecure)." NL);
-    apr_file_printf(errfile, " -p  Do not encrypt the password (plaintext)." NL);
-    apr_file_printf(errfile, " -s  Force SHA encryption of the password"
-            " (insecure)." NL);
-    apr_file_printf(errfile, " -b  Use the password from the command line "
-            "rather than prompting for it." NL);
-    apr_file_printf(errfile, " -D  Delete the specified user." NL);
-    apr_file_printf(errfile,
-            "On other systems than Windows and NetWare the '-p' flag will "
-            "probably not work." NL);
-    apr_file_printf(errfile,
-            "The SHA algorithm does not use a salt and is less secure than "
-            "the MD5 algorithm." NL);
+    apr_file_printf(errfile, "Usage:" NL
+        "\thtpasswd [-cimBdpsD] [-C cost] passwordfile username" NL
+        "\thtpasswd -b[cmBdpsD] [-C cost] passwordfile username password" NL
+        NL
+        "\thtpasswd -n[imBdps] [-C cost] username" NL
+        "\thtpasswd -nb[mBdps] [-C cost] username password" NL
+        " -c  Create a new file." NL
+        " -n  Don't update file; display results on stdout." NL
+        " -b  Use the password from the command line rather than prompting "
+            "for it." NL
+        " -i  Read password from stdin without verification (for script usage)." NL
+        " -m  Force MD5 encryption of the password (default)." NL
+        " -B  Force bcrypt encryption of the password (very secure)." NL
+        " -C  Set the computing time used for the bcrypt algorithm" NL
+        "     (higher is more secure but slower, default: %d, valid: 4 to 31)." NL
+        " -d  Force CRYPT encryption of the password (8 chars max, insecure)." NL
+        " -s  Force SHA encryption of the password (insecure)." NL
+        " -p  Do not encrypt the password (plaintext, insecure)." NL
+        " -D  Delete the specified user." NL
+        "On other systems than Windows and NetWare the '-p' flag will "
+            "probably not work." NL
+        "The SHA algorithm does not use a salt and is less secure than the "
+            "MD5 algorithm." NL,
+        BCRYPT_DEFAULT_COST
+    );
     exit(ERR_SYNTAX);
 }
 
 /*
  * Check to see if the specified file can be opened for the given
  * access.
