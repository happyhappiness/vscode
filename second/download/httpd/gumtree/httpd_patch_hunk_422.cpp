 
     /* firstly, try a proxy, unless a NoProxy directive is active */
     if (!direct_connect) {
         for (i = 0; i < proxies->nelts; i++) {
             p2 = ap_strchr_c(ents[i].scheme, ':');  /* is it a partial URL? */
             if (strcmp(ents[i].scheme, "*") == 0 ||
-                (ents[i].use_regex && ap_regexec(ents[i].regexp, url, 0,NULL, 0)) ||
+                (ents[i].use_regex && 
+                 ap_regexec(ents[i].regexp, url, 0,NULL, 0) == 0) ||
                 (p2 == NULL && strcasecmp(scheme, ents[i].scheme) == 0) ||
                 (p2 != NULL &&
                  strncasecmp(url, ents[i].scheme, strlen(ents[i].scheme)) == 0)) {
 
                 /* handle the scheme */
                 ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
