     while (*strend && apr_isspace(*strend))
         ++strend;
     *line = strend;
     return res;
 }
 
-/* Check a string for any ${ENV} environment variable
- * construct and replace each them by the value of
- * that environment variable, if it exists. If the
- * environment value does not exist, leave the ${ENV}
- * construct alone; it means something else.
- */
-AP_DECLARE(const char *) ap_resolve_env(apr_pool_t *p, const char * word)
-{
-# define SMALL_EXPANSION 5
-    struct sll {
-        struct sll *next;
-        const char *string;
-        apr_size_t len;
-    } *result, *current, sresult[SMALL_EXPANSION];
-    char *res_buf, *cp;
-    const char *s, *e, *ep;
-    unsigned spc;
-    apr_size_t outlen;
-
-    s = ap_strchr_c(word, '$');
-    if (!s) {
-        return word;
-    }
-
-    /* well, actually something to do */
-    ep = word + strlen(word);
-    spc = 0;
-    result = current = &(sresult[spc++]);
-    current->next = NULL;
-    current->string = word;
-    current->len = s - word;
-    outlen = current->len;
-
-    do {
-        /* prepare next entry */
-        if (current->len) {
-            current->next = (spc < SMALL_EXPANSION)
-                            ? &(sresult[spc++])
-                            : (struct sll *)apr_palloc(p,
-                                                       sizeof(*current->next));
-            current = current->next;
-            current->next = NULL;
-            current->len = 0;
-        }
-
-        if (*s == '$') {
-            if (s[1] == '{' && (e = ap_strchr_c(s, '}'))) {
-                word = getenv(apr_pstrndup(p, s+2, e-s-2));
-                if (word) {
-                    current->string = word;
-                    current->len = strlen(word);
-                    outlen += current->len;
-                }
-                else {
-                    current->string = s;
-                    current->len = e - s + 1;
-                    outlen += current->len;
-                }
-                s = e + 1;
-            }
-            else {
-                current->string = s++;
-                current->len = 1;
-                ++outlen;
-            }
-        }
-        else {
-            word = s;
-            s = ap_strchr_c(s, '$');
-            current->string = word;
-            current->len = s ? s - word : ep - word;
-            outlen += current->len;
-        }
-    } while (s && *s);
-
-    /* assemble result */
-    res_buf = cp = apr_palloc(p, outlen + 1);
-    do {
-        if (result->len) {
-            memcpy(cp, result->string, result->len);
-            cp += result->len;
-        }
-        result = result->next;
-    } while (result);
-    res_buf[outlen] = '\0';
-
-    return res_buf;
-}
-
 AP_DECLARE(int) ap_cfg_closefile(ap_configfile_t *cfp)
 {
 #ifdef DEBUG
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL, APLOGNO(00551)
         "Done with config file %s", cfp->name);
 #endif
     return (cfp->close == NULL) ? 0 : cfp->close(cfp->param);
 }
 
+/* we can't use apr_file_* directly because of linking issues on Windows */
 static apr_status_t cfg_close(void *param)
 {
-    apr_file_t *cfp = (apr_file_t *) param;
-    return (apr_file_close(cfp));
+    return apr_file_close(param);
 }
 
-static int cfg_getch(void *param)
+static apr_status_t cfg_getch(char *ch, void *param)
 {
-    char ch;
-    apr_file_t *cfp = (apr_file_t *) param;
-    if (apr_file_getc(&ch, cfp) == APR_SUCCESS)
-        return ch;
-    return (int)EOF;
+    return apr_file_getc(ch, param);
 }
 
-static void *cfg_getstr(void *buf, size_t bufsiz, void *param)
+static apr_status_t cfg_getstr(void *buf, apr_size_t bufsiz, void *param)
 {
-    apr_file_t *cfp = (apr_file_t *) param;
-    apr_status_t rv;
-    rv = apr_file_gets(buf, bufsiz, cfp);
-    if (rv == APR_SUCCESS) {
-        return buf;
-    }
-    return NULL;
+    return apr_file_gets(buf, bufsiz, param);
 }
 
 /* Open a ap_configfile_t as FILE, return open ap_configfile_t struct pointer */
 AP_DECLARE(apr_status_t) ap_pcfg_openfile(ap_configfile_t **ret_cfg,
                                           apr_pool_t *p, const char *name)
 {
