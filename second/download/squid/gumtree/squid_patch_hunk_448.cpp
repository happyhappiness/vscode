     {X509_V_ERR_AKID_SKID_MISMATCH,
      "X509_V_ERR_AKID_SKID_MISMATCH"},
     {X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH,
      "X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH"},
     {X509_V_ERR_KEYUSAGE_NO_CERTSIGN,
      "X509_V_ERR_KEYUSAGE_NO_CERTSIGN"},
+#if defined(X509_V_ERR_UNABLE_TO_GET_CRL_ISSUER)
+    {
+        X509_V_ERR_UNABLE_TO_GET_CRL_ISSUER, //33
+        "X509_V_ERR_UNABLE_TO_GET_CRL_ISSUER"
+    },
+#endif
+#if defined(X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION)
+    {
+        X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION, //34
+        "X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION"
+    },
+#endif
+#if defined(X509_V_ERR_KEYUSAGE_NO_CRL_SIGN)
+    {
+        X509_V_ERR_KEYUSAGE_NO_CRL_SIGN, //35
+        "X509_V_ERR_KEYUSAGE_NO_CRL_SIGN"
+    },
+#endif
+#if defined(X509_V_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION)
+    {
+        X509_V_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION, //36
+        "X509_V_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION"
+    },
+#endif
+#if defined(X509_V_ERR_INVALID_NON_CA)
+    {
+        X509_V_ERR_INVALID_NON_CA, //37
+        "X509_V_ERR_INVALID_NON_CA"
+    },
+#endif
+#if defined(X509_V_ERR_PROXY_PATH_LENGTH_EXCEEDED)
+    {
+        X509_V_ERR_PROXY_PATH_LENGTH_EXCEEDED, //38
+        "X509_V_ERR_PROXY_PATH_LENGTH_EXCEEDED"
+    },
+#endif
+#if defined(X509_V_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE)
+    {
+        X509_V_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE, //39
+        "X509_V_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE"
+    },
+#endif
+#if defined(X509_V_ERR_PROXY_CERTIFICATES_NOT_ALLOWED)
+    {
+        X509_V_ERR_PROXY_CERTIFICATES_NOT_ALLOWED, //40
+        "X509_V_ERR_PROXY_CERTIFICATES_NOT_ALLOWED"
+    },
+#endif
+#if defined(X509_V_ERR_INVALID_EXTENSION)
+    {
+        X509_V_ERR_INVALID_EXTENSION, //41
+        "X509_V_ERR_INVALID_EXTENSION"
+    },
+#endif
+#if defined(X509_V_ERR_INVALID_POLICY_EXTENSION)
+    {
+        X509_V_ERR_INVALID_POLICY_EXTENSION, //42
+        "X509_V_ERR_INVALID_POLICY_EXTENSION"
+    },
+#endif
+#if defined(X509_V_ERR_NO_EXPLICIT_POLICY)
+    {
+        X509_V_ERR_NO_EXPLICIT_POLICY, //43
+        "X509_V_ERR_NO_EXPLICIT_POLICY"
+    },
+#endif
+#if defined(X509_V_ERR_DIFFERENT_CRL_SCOPE)
+    {
+        X509_V_ERR_DIFFERENT_CRL_SCOPE, //44
+        "X509_V_ERR_DIFFERENT_CRL_SCOPE"
+    },
+#endif
+#if defined(X509_V_ERR_UNSUPPORTED_EXTENSION_FEATURE)
+    {
+        X509_V_ERR_UNSUPPORTED_EXTENSION_FEATURE, //45
+        "X509_V_ERR_UNSUPPORTED_EXTENSION_FEATURE"
+    },
+#endif
+#if defined(X509_V_ERR_UNNESTED_RESOURCE)
+    {
+        X509_V_ERR_UNNESTED_RESOURCE, //46
+        "X509_V_ERR_UNNESTED_RESOURCE"
+    },
+#endif
+#if defined(X509_V_ERR_PERMITTED_VIOLATION)
+    {
+        X509_V_ERR_PERMITTED_VIOLATION, //47
+        "X509_V_ERR_PERMITTED_VIOLATION"
+    },
+#endif
+#if defined(X509_V_ERR_EXCLUDED_VIOLATION)
+    {
+        X509_V_ERR_EXCLUDED_VIOLATION, //48
+        "X509_V_ERR_EXCLUDED_VIOLATION"
+    },
+#endif
+#if defined(X509_V_ERR_SUBTREE_MINMAX)
+    {
+        X509_V_ERR_SUBTREE_MINMAX, //49
+        "X509_V_ERR_SUBTREE_MINMAX"
+    },
+#endif
+#if defined(X509_V_ERR_UNSUPPORTED_CONSTRAINT_TYPE)
+    {
+        X509_V_ERR_UNSUPPORTED_CONSTRAINT_TYPE, //51
+        "X509_V_ERR_UNSUPPORTED_CONSTRAINT_TYPE"
+    },
+#endif
+#if defined(X509_V_ERR_UNSUPPORTED_CONSTRAINT_SYNTAX)
+    {
+        X509_V_ERR_UNSUPPORTED_CONSTRAINT_SYNTAX, //52
+        "X509_V_ERR_UNSUPPORTED_CONSTRAINT_SYNTAX"
+    },
+#endif
+#if defined(X509_V_ERR_UNSUPPORTED_NAME_SYNTAX)
+    {
+        X509_V_ERR_UNSUPPORTED_NAME_SYNTAX, //53
+        "X509_V_ERR_UNSUPPORTED_NAME_SYNTAX"
+    },
+#endif
+#if defined(X509_V_ERR_CRL_PATH_VALIDATION_ERROR)
+    {
+        X509_V_ERR_CRL_PATH_VALIDATION_ERROR, //54
+        "X509_V_ERR_CRL_PATH_VALIDATION_ERROR"
+    },
+#endif
     {X509_V_ERR_APPLICATION_VERIFICATION,
      "X509_V_ERR_APPLICATION_VERIFICATION"},
     { SSL_ERROR_NONE, "SSL_ERROR_NONE"},
     {SSL_ERROR_NONE, NULL}
 };
 
+static const char *OptionalSslErrors[] = {
+    "X509_V_ERR_UNABLE_TO_GET_CRL_ISSUER",
+    "X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION",
+    "X509_V_ERR_KEYUSAGE_NO_CRL_SIGN",
+    "X509_V_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION",
+    "X509_V_ERR_INVALID_NON_CA",
+    "X509_V_ERR_PROXY_PATH_LENGTH_EXCEEDED",
+    "X509_V_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE",
+    "X509_V_ERR_PROXY_CERTIFICATES_NOT_ALLOWED",
+    "X509_V_ERR_INVALID_EXTENSION",
+    "X509_V_ERR_INVALID_POLICY_EXTENSION",
+    "X509_V_ERR_NO_EXPLICIT_POLICY",
+    "X509_V_ERR_DIFFERENT_CRL_SCOPE",
+    "X509_V_ERR_UNSUPPORTED_EXTENSION_FEATURE",
+    "X509_V_ERR_UNNESTED_RESOURCE",
+    "X509_V_ERR_PERMITTED_VIOLATION",
+    "X509_V_ERR_EXCLUDED_VIOLATION",
+    "X509_V_ERR_SUBTREE_MINMAX",
+    "X509_V_ERR_UNSUPPORTED_CONSTRAINT_TYPE",
+    "X509_V_ERR_UNSUPPORTED_CONSTRAINT_SYNTAX",
+    "X509_V_ERR_UNSUPPORTED_NAME_SYNTAX",
+    "X509_V_ERR_CRL_PATH_VALIDATION_ERROR",
+    NULL
+};
+
+struct SslErrorAlias {
+    const char *name;
+    const Ssl::ssl_error_t *errors;
+};
+
+static const Ssl::ssl_error_t hasExpired[] = {X509_V_ERR_CERT_HAS_EXPIRED, SSL_ERROR_NONE};
+static const Ssl::ssl_error_t notYetValid[] = {X509_V_ERR_CERT_NOT_YET_VALID, SSL_ERROR_NONE};
+static const Ssl::ssl_error_t domainMismatch[] = {SQUID_X509_V_ERR_DOMAIN_MISMATCH, SSL_ERROR_NONE};
+static const Ssl::ssl_error_t certUntrusted[] = {X509_V_ERR_INVALID_CA,
+        X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN,
+        X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE,
+        X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT,
+        X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY,
+        X509_V_ERR_CERT_UNTRUSTED, SSL_ERROR_NONE
+                                                };
+static const Ssl::ssl_error_t certSelfSigned[] = {X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT, SSL_ERROR_NONE};
+
+// The list of error name shortcuts  for use with ssl_error acls.
+// The keys without the "ssl::" scope prefix allow shorter error
+// names within the SSL options scope. This is easier than
+// carefully stripping the scope prefix in Ssl::ParseErrorString().
+static SslErrorAlias TheSslErrorShortcutsArray[] = {
+    {"ssl::certHasExpired", hasExpired},
+    {"certHasExpired", hasExpired},
+    {"ssl::certNotYetValid", notYetValid},
+    {"certNotYetValid", notYetValid},
+    {"ssl::certDomainMismatch", domainMismatch},
+    {"certDomainMismatch", domainMismatch},
+    {"ssl::certUntrusted", certUntrusted},
+    {"certUntrusted", certUntrusted},
+    {"ssl::certSelfSigned", certSelfSigned},
+    {"certSelfSigned", certSelfSigned},
+    {NULL, NULL}
+};
+
+// Use std::map to optimize search.
+typedef std::map<std::string, const Ssl::ssl_error_t *> SslErrorShortcuts;
+SslErrorShortcuts TheSslErrorShortcuts;
+
 static void loadSslErrorMap()
 {
     assert(TheSslErrors.empty());
     for (int i = 0; TheSslErrorArray[i].name; ++i) {
         TheSslErrors[TheSslErrorArray[i].value] = &TheSslErrorArray[i];
     }
 }
 
+static void loadSslErrorShortcutsMap()
+{
+    assert(TheSslErrorShortcuts.empty());
+    for (int i = 0; TheSslErrorShortcutsArray[i].name; ++i)
+        TheSslErrorShortcuts[TheSslErrorShortcutsArray[i].name] = TheSslErrorShortcutsArray[i].errors;
+}
+
 Ssl::ssl_error_t Ssl::GetErrorCode(const char *name)
 {
     //TODO: use a std::map?
     for (int i = 0; TheSslErrorArray[i].name != NULL; ++i) {
         if (strcmp(name, TheSslErrorArray[i].name) == 0)
             return TheSslErrorArray[i].value;
     }
     return SSL_ERROR_NONE;
 }
 
-Ssl::ssl_error_t
+Ssl::Errors *
 Ssl::ParseErrorString(const char *name)
 {
     assert(name);
 
     const Ssl::ssl_error_t ssl_error = GetErrorCode(name);
     if (ssl_error != SSL_ERROR_NONE)
-        return ssl_error;
+        return new Ssl::Errors(ssl_error);
 
     if (xisdigit(*name)) {
         const long int value = strtol(name, NULL, 0);
         if (SQUID_SSL_ERROR_MIN <= value && value <= SQUID_SSL_ERROR_MAX)
-            return value;
+            return new Ssl::Errors(value);
         fatalf("Too small or too bug SSL error code '%s'", name);
     }
 
+    if (TheSslErrorShortcuts.empty())
+        loadSslErrorShortcutsMap();
+
+    const SslErrorShortcuts::const_iterator it = TheSslErrorShortcuts.find(name);
+    if (it != TheSslErrorShortcuts.end()) {
+        // Should not be empty...
+        assert(it->second[0] != SSL_ERROR_NONE);
+        Ssl::Errors *errors = new Ssl::Errors(it->second[0]);
+        for (int i =1; it->second[i] != SSL_ERROR_NONE; ++i) {
+            errors->push_back_unique(it->second[i]);
+        }
+        return errors;
+    }
+
     fatalf("Unknown SSL error name '%s'", name);
-    return SSL_ERROR_SSL; // not reached
+    return NULL; // not reached
 }
 
 const char *Ssl::GetErrorName(Ssl::ssl_error_t value)
 {
     if (TheSslErrors.empty())
         loadSslErrorMap();
