     //   2) if this line is "ftp_epsv on|off" and already exist rules of "ftp_epsv allow|deny ..."
     // then abort
     if ((!ftpEpsvIsDeprecatedRule && FtpEspvDeprecated) ||
             (ftpEpsvIsDeprecatedRule && !FtpEspvDeprecated && *ftp_epsv != NULL)) {
         debugs(3, DBG_CRITICAL, "FATAL: do not mix \"ftp_epsv on|off\" cfg lines with \"ftp_epsv allow|deny ...\" cfg lines. Update your ftp_epsv rules.");
         self_destruct();
+        return;
     }
 
     if (ftpEpsvIsDeprecatedRule) {
         // overwrite previous ftp_epsv lines
         delete *ftp_epsv;
+        *ftp_epsv = nullptr;
+
         if (ftpEpsvDeprecatedAction == allow_t(ACCESS_DENIED)) {
-            Acl::AndNode *ftpEpsvRule = new Acl::AndNode;
-            ftpEpsvRule->context("(ftp_epsv rule)", config_input_line);
-            ACL *a = ACL::FindByName("all");
-            if (!a) {
+            if (ACL *a = ACL::FindByName("all"))
+                ParseAclWithAction(ftp_epsv, ftpEpsvDeprecatedAction, "ftp_epsv", a);
+            else {
                 self_destruct();
                 return;
             }
-            ftpEpsvRule->add(a);
-            *ftp_epsv = new Acl::Tree;
-            (*ftp_epsv)->context("(ftp_epsv rules)", config_input_line);
-            (*ftp_epsv)->add(ftpEpsvRule, ftpEpsvDeprecatedAction);
-        } else
-            *ftp_epsv = NULL;
+        }
         FtpEspvDeprecated = true;
     } else {
         aclParseAccessLine(cfg_directive, LegacyParser, ftp_epsv);
     }
 }
 
 static void dump_ftp_epsv(StoreEntry *entry, const char *name, acl_access *ftp_epsv)
 {
     if (ftp_epsv)
-        dump_SBufList(entry, ftp_epsv->treeDump(name, NULL));
+        dump_SBufList(entry, ftp_epsv->treeDump(name, Acl::AllowOrDeny));
 }
 
 static void free_ftp_epsv(acl_access **ftp_epsv)
 {
     free_acl_access(ftp_epsv);
     FtpEspvDeprecated = false;
 }
 
 static void
-parse_configuration_includes_quoted_values(bool *recognizeQuotedValues)
+parse_UrlHelperTimeout(SquidConfig::UrlHelperTimeout *config)
+{
+    time_msec_t tval;
+    parseTimeLine(&tval, T_SECOND_STR, false, true);
+    Config.Timeout.urlRewrite = static_cast<time_t>(tval/1000);
+
+    char *key, *value;
+    while(ConfigParser::NextKvPair(key, value)) {
+        if (strcasecmp(key, "on_timeout") == 0) {
+            if (strcasecmp(value, "bypass") == 0)
+                config->action = toutActBypass;
+            else if (strcasecmp(value, "fail") == 0)
+                config->action = toutActFail;
+            else if (strcasecmp(value, "retry") == 0)
+                config->action = toutActRetry;
+            else if (strcasecmp(value, "use_configured_response") == 0) {
+                config->action = toutActUseConfiguredResponse;
+            } else {
+                debugs(3, DBG_CRITICAL, "FATAL: unsuported \"on_timeout\"  action:" << value);
+                self_destruct();
+                return;
+            }
+        } else if (strcasecmp(key, "response") == 0) {
+            config->response = xstrdup(value);
+        } else {
+            debugs(3, DBG_CRITICAL, "FATAL: unsuported option " << key);
+            self_destruct();
+            return;
+        }
+    }
+
+    if (config->action == toutActUseConfiguredResponse && !config->response) {
+        debugs(3, DBG_CRITICAL, "FATAL: Expected 'response=' option after 'on_timeout=use_configured_response' option");
+        self_destruct();
+    }
+
+    if (config->action != toutActUseConfiguredResponse && config->response) {
+        debugs(3, DBG_CRITICAL, "FATAL: 'response=' option is valid only when used with the  'on_timeout=use_configured_response' option");
+        self_destruct();
+    }
+}
+
+static void
+dump_UrlHelperTimeout(StoreEntry *entry, const char *name, SquidConfig::UrlHelperTimeout &config)
+{
+    const char  *onTimedOutActions[] = {"bypass", "fail", "retry", "use_configured_response"};
+    assert(config.action >= 0 && config.action <= toutActUseConfiguredResponse);
+
+    dump_time_t(entry, name, Config.Timeout.urlRewrite);
+    storeAppendPrintf(entry, " on_timeout=%s", onTimedOutActions[config.action]);
+
+    if (config.response)
+        storeAppendPrintf(entry, " response=\"%s\"", config.response);
+
+    storeAppendPrintf(entry, "\n");
+}
+
+static void
+free_UrlHelperTimeout(SquidConfig::UrlHelperTimeout *config)
+{
+    Config.Timeout.urlRewrite = 0;
+    config->action = 0;
+    safe_free(config->response);
+}
+
+static void
+parse_configuration_includes_quoted_values(bool *)
 {
     int val = 0;
     parse_onoff(&val);
 
     // If quoted values is set to on then enable new strict mode parsing
     if (val) {
