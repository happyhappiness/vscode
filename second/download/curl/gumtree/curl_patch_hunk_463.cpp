     *val = atoi(str);
   else
     retcode = 1; /* badness */
   return retcode;
 }
 
+/*
+ * Parse the string and modify the long in the given address. Return
+ * non-zero on failure, zero on success.
+ *
+ * The string is a list of protocols
+ *
+ * Since this function gets called with the 'nextarg' pointer from within the
+ * getparameter a lot, we must check it for NULL before accessing the str
+ * data.
+ */
+
+static long proto2num(struct Configurable *config, long *val, const char *str)
+{
+  char *buffer;
+  const char *sep = ",";
+  char *token;
+
+  static struct sprotos {
+    const char *name;
+    long bit;
+  } const protos[] = {
+    { "all", CURLPROTO_ALL },
+    { "http", CURLPROTO_HTTP },
+    { "https", CURLPROTO_HTTPS },
+    { "ftp", CURLPROTO_FTP },
+    { "ftps", CURLPROTO_FTPS },
+    { "scp", CURLPROTO_SCP },
+    { "sftp", CURLPROTO_SFTP },
+    { "telnet", CURLPROTO_TELNET },
+    { "ldap", CURLPROTO_LDAP },
+    { "ldaps", CURLPROTO_LDAPS },
+    { "dict", CURLPROTO_DICT },
+    { "file", CURLPROTO_FILE },
+    { "tftp", CURLPROTO_TFTP },
+    { "imap", CURLPROTO_IMAP },
+    { "imaps", CURLPROTO_IMAPS },
+    { "pop3", CURLPROTO_POP3 },
+    { "pop3s", CURLPROTO_POP3S },
+    { "smtp", CURLPROTO_SMTP },
+    { "smtps", CURLPROTO_SMTPS },
+    { "rtsp", CURLPROTO_RTSP },
+    { NULL, 0 }
+  };
+
+  if(!str)
+    return 1;
+
+  buffer = strdup(str); /* because strtok corrupts it */
+
+  for (token = strtok(buffer, sep);
+       token;
+       token = strtok(NULL, sep)) {
+    enum e_action { allow, deny, set } action = allow;
+
+    struct sprotos const *pp;
+
+    /* Process token modifiers */
+    while (!ISALNUM(*token)) { /* may be NULL if token is all modifiers */
+      switch (*token++) {
+      case '=':
+        action = set;
+        break;
+      case '-':
+        action = deny;
+        break;
+      case '+':
+        action = allow;
+        break;
+      default: /* Includes case of terminating NULL */
+        free(buffer);
+        return 1;
+      }
+    }
+
+    for (pp=protos; pp->name; pp++) {
+      if (curlx_raw_equal(token, pp->name)) {
+        switch (action) {
+        case deny:
+          *val &= ~(pp->bit);
+          break;
+        case allow:
+          *val |= pp->bit;
+          break;
+        case set:
+          *val = pp->bit;
+          break;
+        }
+        break;
+      }
+    }
+
+    if (!(pp->name)) { /* unknown protocol */
+      /* If they have specified only this protocol, we say treat it as
+         if no protocols are allowed */
+      if (action == set)
+        *val = 0;
+      warnf(config, "unrecognized protocol '%s'\n", token);
+    }
+  }
+  free(buffer);
+  return 0;
+}
+
 /**
  * Parses the given string looking for an offset (which may be
  * a larger-than-integer value).
  *
  * @param val  the offset to populate
  * @param str  the buffer containing the offset
  * @return zero if successful, non-zero if failure.
  */
 static int str2offset(curl_off_t *val, const char *str)
 {
 #if (CURL_SIZEOF_CURL_OFF_T > CURL_SIZEOF_LONG)
   *val = curlx_strtoofft(str, NULL, 0);
-  if((*val == CURL_LLONG_MAX || *val == CURL_LLONG_MIN) && (ERRNO == ERANGE))
+  if((*val == CURL_OFF_T_MAX || *val == CURL_OFF_T_MIN) && (ERRNO == ERANGE))
     return 1;
 #else
   *val = strtol(str, NULL, 0);
   if ((*val == LONG_MIN || *val == LONG_MAX) && ERRNO == ERANGE)
     return 1;
 #endif
