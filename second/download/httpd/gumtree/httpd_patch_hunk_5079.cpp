     /* find the scheme */
     u = strchr(url, ':');
     if (u == NULL || u[1] != '/' || u[2] != '/' || u[3] == '\0')
        return DECLINED;
     if ((u - url) > 14)
         return HTTP_BAD_REQUEST;
-    scheme = apr_pstrndup(p, url, u - url);
+    scheme = apr_pstrmemdup(p, url, u - url);
     /* scheme is lowercase */
     ap_str_tolower(scheme);
     /* is it for us? */
     if (strcmp(scheme, "https") == 0) {
         if (!ap_proxy_ssl_enable(NULL)) {
             ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01112)
