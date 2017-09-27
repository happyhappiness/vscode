 
     /* just make sure that we are really meant! */
     if (strncmp(r->filename, "redirect:", 9) != 0) {
         return DECLINED;
     }
 
+    if (is_redirect_limit_exceeded(r)) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                      "mod_rewrite: maximum number of internal redirects "
+                      "reached. Assuming configuration error. Use "
+                      "'RewriteOptions MaxRedirects' to increase the limit "
+                      "if neccessary.");
+        return HTTP_INTERNAL_SERVER_ERROR;
+    }
+
     /* now do the internal redirect */
     ap_internal_redirect(apr_pstrcat(r->pool, r->filename+9,
-                                    r->args ? "?" : NULL, r->args, NULL), r);
+                                     r->args ? "?" : NULL, r->args, NULL), r);
 
     /* and return gracefully */
     return OK;
 }
 
+/*
+ * check whether redirect limit is reached
+ */
+static int is_redirect_limit_exceeded(request_rec *r)
+{
+    request_rec *top = r;
+    rewrite_request_conf *reqc;
+    rewrite_perdir_conf *dconf;
+
+    /* we store it in the top request */
+    while (top->main) {
+        top = top->main;
+    }
+    while (top->prev) {
+        top = top->prev;
+    }
+
+    /* fetch our config */
+    reqc = (rewrite_request_conf *) ap_get_module_config(top->request_config,
+                                                         &rewrite_module);
+
+    /* no config there? create one. */
+    if (!reqc) {
+        rewrite_server_conf *sconf;
+
+        reqc = apr_palloc(top->pool, sizeof(rewrite_request_conf));
+        sconf = ap_get_module_config(r->server->module_config, &rewrite_module);
+
+        reqc->redirects = 0;
+        reqc->redirect_limit = sconf->redirect_limit
+                                 ? sconf->redirect_limit
+                                 : REWRITE_REDIRECT_LIMIT;
+
+        /* associate it with this request */
+        ap_set_module_config(top->request_config, &rewrite_module, reqc);
+    }
+
+    /* allow to change the limit during redirects. */
+    dconf = (rewrite_perdir_conf *)ap_get_module_config(r->per_dir_config,
+                                                        &rewrite_module);
+
+    /* 0 == unset; take server conf ... */
+    if (dconf->redirect_limit) {
+        reqc->redirect_limit = dconf->redirect_limit;
+    }
+
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                  "mod_rewrite's internal redirect status: %d/%d.",
+                  reqc->redirects, reqc->redirect_limit);
+
+    /* and now give the caller a hint */
+    return (reqc->redirects++ >= reqc->redirect_limit);
+}
+
 
 /*
 ** +-------------------------------------------------------+
 ** |                                                       |
 ** |                  the rewriting engine
 ** |                                                       |
