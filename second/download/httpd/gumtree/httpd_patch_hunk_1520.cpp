 
 #include "apr_strings.h"
 #include "apr_file_info.h"
 #include "apr_user.h"
 
 #include "ap_config.h"
+#include "ap_provider.h"
 #include "httpd.h"
 #include "http_config.h"
 #include "http_core.h"
 #include "http_log.h"
 #include "http_protocol.h"
 #include "http_request.h"
 
-#include "mod_auth.h"     /* for AUTHZ_GROUP_NOTE */
+#include "mod_auth.h"
 
-typedef struct {
-    int authoritative;
-} authz_owner_config_rec;
-
-static void *create_authz_owner_dir_config(apr_pool_t *p, char *d)
-{
-    authz_owner_config_rec *conf = apr_palloc(p, sizeof(*conf));
-
-    conf->authoritative = 1; /* keep the fortress secure by default */
-    return conf;
-}
+APR_DECLARE_OPTIONAL_FN(char*, authz_owner_get_file_group, (request_rec *r));
 
 static const command_rec authz_owner_cmds[] =
 {
-    AP_INIT_FLAG("AuthzOwnerAuthoritative", ap_set_flag_slot,
-                 (void *)APR_OFFSETOF(authz_owner_config_rec, authoritative),
-                 OR_AUTHCFG,
-                 "Set to 'Off' to allow access control to be passed along to "
-                 "lower modules. (default is On.)"),
     {NULL}
 };
 
 module AP_MODULE_DECLARE_DATA authz_owner_module;
 
-static int check_file_owner(request_rec *r)
+static authz_status fileowner_check_authorization(request_rec *r,
+                                             const char *require_args)
 {
-    authz_owner_config_rec *conf = ap_get_module_config(r->per_dir_config,
-                                                        &authz_owner_module);
-    int m = r->method_number;
-    register int x;
-    const char *t, *w;
-    const apr_array_header_t *reqs_arr = ap_requires(r);
-    require_line *reqs;
-    int required_owner = 0;
-    apr_status_t status = 0;
     char *reason = NULL;
+    apr_status_t status = 0;
 
-    if (!reqs_arr) {
-        return DECLINED;
-    }
+#if !APR_HAS_USER
+    reason = "'Require file-owner' is not supported on this platform.";
+    ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+                  "Authorization of user %s to access %s failed, reason: %s",
+                  r->user, r->uri, reason ? reason : "unknown");
+    return AUTHZ_DENIED;
+#else  /* APR_HAS_USER */
+    char *owner = NULL;
+    apr_finfo_t finfo;
 
-    reqs = (require_line *)reqs_arr->elts;
-    for (x = 0; x < reqs_arr->nelts; x++) {
+    if (!r->user) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            "access to %s failed, reason: no authenticated user", r->uri);
+        return AUTHZ_DENIED;
+    }
 
-        /* if authoritative = On then break if a require already failed. */
-        if (reason && conf->authoritative) {
-            break;
-        }
+    if (!r->filename) {
+        reason = "no filename available";
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+                      "Authorization of user %s to access %s failed, reason: %s",
+                      r->user, r->uri, reason ? reason : "unknown");
+        return AUTHZ_DENIED;
+    }
 
-        if (!(reqs[x].method_mask & (AP_METHOD_BIT << m))) {
-            continue;
-        }
+    status = apr_stat(&finfo, r->filename, APR_FINFO_USER, r->pool);
+    if (status != APR_SUCCESS) {
+        reason = apr_pstrcat(r->pool, "could not stat file ",
+                                r->filename, NULL);
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+                      "Authorization of user %s to access %s failed, reason: %s",
+                      r->user, r->uri, reason ? reason : "unknown");
+        return AUTHZ_DENIED;
+    }
 
-        t = reqs[x].requirement;
-        w = ap_getword_white(r->pool, &t);
+    if (!(finfo.valid & APR_FINFO_USER)) {
+        reason = "no file owner information available";
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+                      "Authorization of user %s to access %s failed, reason: %s",
+                      r->user, r->uri, reason ? reason : "unknown");
+        return AUTHZ_DENIED;
+    }
 
-        if (!strcmp(w, "file-owner")) {
-#if !APR_HAS_USER
-            if ((required_owner & ~1) && conf->authoritative) {
-                break;
-            }
-
-            required_owner |= 1; /* remember the requirement */
-            reason = "'Require file-owner' is not supported on this platform.";
-            continue;
-#else  /* APR_HAS_USER */
-            char *owner = NULL;
-            apr_finfo_t finfo;
+    status = apr_uid_name_get(&owner, finfo.user, r->pool);
+    if (status != APR_SUCCESS || !owner) {
+        reason = "could not get name of file owner";
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+                      "Authorization of user %s to access %s failed, reason: %s",
+                      r->user, r->uri, reason ? reason : "unknown");
+        return AUTHZ_DENIED;
+    }
 
-            if ((required_owner & ~1) && conf->authoritative) {
-                break;
-            }
-
-            required_owner |= 1; /* remember the requirement */
-
-            if (!r->filename) {
-                reason = "no filename available";
-                continue;
-            }
-
-            status = apr_stat(&finfo, r->filename, APR_FINFO_USER, r->pool);
-            if (status != APR_SUCCESS) {
-                reason = apr_pstrcat(r->pool, "could not stat file ",
-                                     r->filename, NULL);
-                continue;
-            }
-
-            if (!(finfo.valid & APR_FINFO_USER)) {
-                reason = "no file owner information available";
-                continue;
-            }
-
-            status = apr_uid_name_get(&owner, finfo.user, r->pool);
-            if (status != APR_SUCCESS || !owner) {
-                reason = "could not get name of file owner";
-                continue;
-            }
-
-            if (strcmp(owner, r->user)) {
-                reason = apr_psprintf(r->pool, "file owner %s does not match.",
-                                      owner);
-                continue;
-            }
+    if (strcmp(owner, r->user)) {
+        reason = apr_psprintf(r->pool, "file owner %s does not match.",
+                                owner);
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+                      "Authorization of user %s to access %s failed, reason: %s",
+                      r->user, r->uri, reason ? reason : "unknown");
+        return AUTHZ_DENIED;
+    }
 
-            /* this user is authorized */
-            return OK;
+    /* this user is authorized */
+    return AUTHZ_GRANTED;
 #endif /* APR_HAS_USER */
-        }
+}
 
-        /* file-group only figures out the file's group and lets
-         * other modules do the actual authorization (against a group file/db).
-         * Thus, these modules have to hook themselves after
-         * mod_authz_owner and of course recognize 'file-group', too.
-         */
-        if (!strcmp(w, "file-group")) {
+static char *authz_owner_get_file_group(request_rec *r)
+{
+    char *reason = NULL;
+
+    /* file-group only figures out the file's group and lets
+    * other modules do the actual authorization (against a group file/db).
+    * Thus, these modules have to hook themselves after
+    * mod_authz_owner and of course recognize 'file-group', too.
+    */
 #if !APR_HAS_USER
-            if ((required_owner & ~6) && conf->authoritative) {
-                break;
-            }
-
-            required_owner |= 2; /* remember the requirement */
-            reason = "'Require file-group' is not supported on this platform.";
-            continue;
+    return NULL;
 #else  /* APR_HAS_USER */
-            char *group = NULL;
-            apr_finfo_t finfo;
+    char *group = NULL;
+    apr_finfo_t finfo;
+    apr_status_t status = 0;
 
-            if ((required_owner & ~6) && conf->authoritative) {
-                break;
-            }
-
-            required_owner |= 2; /* remember the requirement */
-
-            if (!r->filename) {
-                reason = "no filename available";
-                continue;
-            }
-
-            status = apr_stat(&finfo, r->filename, APR_FINFO_GROUP, r->pool);
-            if (status != APR_SUCCESS) {
-                reason = apr_pstrcat(r->pool, "could not stat file ",
-                                     r->filename, NULL);
-                continue;
-            }
-
-            if (!(finfo.valid & APR_FINFO_GROUP)) {
-                reason = "no file group information available";
-                continue;
-            }
-
-            status = apr_gid_name_get(&group, finfo.group, r->pool);
-            if (status != APR_SUCCESS || !group) {
-                reason = "could not get name of file group";
-                continue;
-            }
-
-            /* store group name in a note and let others decide... */
-            apr_table_setn(r->notes, AUTHZ_GROUP_NOTE, group);
-            required_owner |= 4;
-            continue;
-#endif /* APR_HAS_USER */
-        }
+    if (!r->filename) {
+        reason = "no filename available";
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+                      "Authorization of user %s to access %s failed, reason: %s",
+                      r->user, r->uri, reason ? reason : "unknown");
+        return NULL;
     }
 
-    if (!required_owner || !conf->authoritative) {
-        return DECLINED;
+    status = apr_stat(&finfo, r->filename, APR_FINFO_GROUP, r->pool);
+    if (status != APR_SUCCESS) {
+        reason = apr_pstrcat(r->pool, "could not stat file ",
+                                r->filename, NULL);
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+                      "Authorization of user %s to access %s failed, reason: %s",
+                      r->user, r->uri, reason ? reason : "unknown");
+        return NULL;
     }
 
-    /* allow file-group passed to group db modules either if this is the
-     * only applicable requirement here or if a file-owner failed but we're
-     * not authoritative.
-     * This allows configurations like:
-     *
-     * AuthzOwnerAuthoritative Off
-     * require file-owner
-     * require file-group
-     *
-     * with the semantical meaning of "either owner or group must match"
-     * (inclusive or)
-     *
-     * [ 6 == 2 | 4; 7 == 1 | 2 | 4 ] should I use #defines instead?
-     */
-    if (required_owner == 6 || (required_owner == 7 && !conf->authoritative)) {
-        return DECLINED;
+    if (!(finfo.valid & APR_FINFO_GROUP)) {
+        reason = "no file group information available";
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+                      "Authorization of user %s to access %s failed, reason: %s",
+                      r->user, r->uri, reason ? reason : "unknown");
+        return NULL;
     }
 
-    ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
-                  "Authorization of user %s to access %s failed, reason: %s",
-                  r->user, r->uri, reason ? reason : "unknown");
+    status = apr_gid_name_get(&group, finfo.group, r->pool);
+    if (status != APR_SUCCESS || !group) {
+        reason = "could not get name of file group";
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+                      "Authorization of user %s to access %s failed, reason: %s",
+                      r->user, r->uri, reason ? reason : "unknown");
+        return NULL;
+    }
 
-    ap_note_auth_failure(r);
-    return HTTP_UNAUTHORIZED;
+    return group;
+#endif /* APR_HAS_USER */
 }
 
+static const authz_provider authz_fileowner_provider =
+{
+    &fileowner_check_authorization,
+};
+
 static void register_hooks(apr_pool_t *p)
 {
-    ap_hook_auth_checker(check_file_owner, NULL, NULL, APR_HOOK_MIDDLE);
+    APR_REGISTER_OPTIONAL_FN(authz_owner_get_file_group);
+
+    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "file-owner",
+                              AUTHZ_PROVIDER_VERSION,
+                              &authz_fileowner_provider,
+                              AP_AUTH_INTERNAL_PER_CONF);
 }
 
-module AP_MODULE_DECLARE_DATA authz_owner_module =
+AP_DECLARE_MODULE(authz_owner) =
 {
     STANDARD20_MODULE_STUFF,
-    create_authz_owner_dir_config, /* dir config creater */
+    NULL,                          /* dir config creater */
     NULL,                          /* dir merger --- default is to override */
     NULL,                          /* server config */
     NULL,                          /* merge server config */
     authz_owner_cmds,              /* command apr_table_t */
     register_hooks                 /* register hooks */
 };
