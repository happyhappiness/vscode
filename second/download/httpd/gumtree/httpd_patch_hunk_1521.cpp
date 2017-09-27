  * limitations under the License.
  */
 
 #include "apr_strings.h"
 
 #include "ap_config.h"
+#include "ap_provider.h"
 #include "httpd.h"
 #include "http_config.h"
 #include "http_core.h"
 #include "http_log.h"
 #include "http_protocol.h"
 #include "http_request.h"
 
+#include "mod_auth.h"
+
 typedef struct {
-    int authoritative;
+        int dummy;  /* just here to stop compiler warnings for now. */
 } authz_user_config_rec;
 
 static void *create_authz_user_dir_config(apr_pool_t *p, char *d)
 {
     authz_user_config_rec *conf = apr_palloc(p, sizeof(*conf));
 
-    conf->authoritative = 1; /* keep the fortress secure by default */
     return conf;
 }
 
 static const command_rec authz_user_cmds[] =
 {
-    AP_INIT_FLAG("AuthzUserAuthoritative", ap_set_flag_slot,
-                 (void *)APR_OFFSETOF(authz_user_config_rec, authoritative),
-                 OR_AUTHCFG,
-                 "Set to 'Off' to allow access control to be passed along to "
-                 "lower modules if the 'require user' or 'require valid-user' "
-                 "statement is not met. (default: On)."),
     {NULL}
 };
 
 module AP_MODULE_DECLARE_DATA authz_user_module;
 
-static int check_user_access(request_rec *r)
+static authz_status user_check_authorization(request_rec *r,
+                                             const char *require_args)
 {
-    authz_user_config_rec *conf = ap_get_module_config(r->per_dir_config,
-                                                       &authz_user_module);
-    char *user = r->user;
-    int m = r->method_number;
-    int required_user = 0;
-    register int x;
     const char *t, *w;
-    const apr_array_header_t *reqs_arr = ap_requires(r);
-    require_line *reqs;
 
-    /* BUG FIX: tadc, 11-Nov-1995.  If there is no "requires" directive,
-     * then any user will do.
-     */
-    if (!reqs_arr) {
-        return DECLINED;
+    if (!r->user) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            "access to %s failed, reason: no authenticated user", r->uri);
+        return AUTHZ_DENIED;
     }
-    reqs = (require_line *)reqs_arr->elts;
-
-    for (x = 0; x < reqs_arr->nelts; x++) {
 
-        if (!(reqs[x].method_mask & (AP_METHOD_BIT << m))) {
-            continue;
-        }
-
-        t = reqs[x].requirement;
-        w = ap_getword_white(r->pool, &t);
-        if (!strcasecmp(w, "valid-user")) {
-            return OK;
-        }
-        if (!strcasecmp(w, "user")) {
-            /* And note that there are applicable requirements
-             * which we consider ourselves the owner of.
-             */
-            required_user = 1;
-            while (t[0]) {
-                w = ap_getword_conf(r->pool, &t);
-                if (!strcmp(user, w)) {
-                    return OK;
-                }
-            }
+    t = require_args;
+    while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
+        if (!strcmp(r->user, w)) {
+            return AUTHZ_GRANTED;
         }
     }
 
-    if (!required_user) {
-        /* no applicable requirements */
-        return DECLINED;
-    }
-
-    if (!conf->authoritative) {
-        return DECLINED;
-    }
-
     ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                   "access to %s failed, reason: user '%s' does not meet "
-                  "'require'ments for user/valid-user to be allowed access",
-                  r->uri, user);
+                  "'require'ments for user to be allowed access",
+                  r->uri, r->user);
 
-    ap_note_auth_failure(r);
-    return HTTP_UNAUTHORIZED;
+    return AUTHZ_DENIED;
 }
 
+static authz_status validuser_check_authorization(request_rec *r, const char *require_line)
+{
+    if (!r->user) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            "access to %s failed, reason: no authenticated user", r->uri);
+        return AUTHZ_DENIED;
+    }
+
+    return AUTHZ_GRANTED;
+}
+
+static const authz_provider authz_user_provider =
+{
+    &user_check_authorization,
+};
+static const authz_provider authz_validuser_provider =
+{
+    &validuser_check_authorization,
+};
+
 static void register_hooks(apr_pool_t *p)
 {
-    ap_hook_auth_checker(check_user_access, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "user",
+                              AUTHZ_PROVIDER_VERSION,
+                              &authz_user_provider, AP_AUTH_INTERNAL_PER_CONF);
+    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "valid-user",
+                              AUTHZ_PROVIDER_VERSION,
+                              &authz_validuser_provider,
+                              AP_AUTH_INTERNAL_PER_CONF);
 }
 
-module AP_MODULE_DECLARE_DATA authz_user_module =
+AP_DECLARE_MODULE(authz_user) =
 {
     STANDARD20_MODULE_STUFF,
     create_authz_user_dir_config, /* dir config creater */
     NULL,                         /* dir merger --- default is to override */
     NULL,                         /* server config */
     NULL,                         /* merge server config */
