 
 static void free_icap_service_failure_limit(Adaptation::Icap::Config *cfg)
 {
     cfg->oldest_service_failure = 0;
     cfg->service_failure_limit = 0;
 }
+#endif
+
+#if USE_SSL
+static void parse_sslproxy_cert_adapt(sslproxy_cert_adapt **cert_adapt)
+{
+    char *al;
+    sslproxy_cert_adapt *ca = (sslproxy_cert_adapt *) xcalloc(1, sizeof(sslproxy_cert_adapt));
+    if ((al = strtok(NULL, w_space)) == NULL) {
+        self_destruct();
+        return;
+    }
+
+    const char *param;
+    if ( char *s = strchr(al, '{')) {
+        *s = '\0'; // terminate the al string
+        ++s;
+        param = s;
+        s = strchr(s, '}');
+        if (!s) {
+            self_destruct();
+            return;
+        }
+        *s = '\0';
+    } else
+        param = NULL;
+
+    if (strcmp(al, Ssl::CertAdaptAlgorithmStr[Ssl::algSetValidAfter]) == 0) {
+        ca->alg = Ssl::algSetValidAfter;
+        ca->param = strdup("on");
+    } else if (strcmp(al, Ssl::CertAdaptAlgorithmStr[Ssl::algSetValidBefore]) == 0) {
+        ca->alg = Ssl::algSetValidBefore;
+        ca->param = strdup("on");
+    } else if (strcmp(al, Ssl::CertAdaptAlgorithmStr[Ssl::algSetCommonName]) == 0) {
+        ca->alg = Ssl::algSetCommonName;
+        if (param) {
+            if (strlen(param) > 64) {
+                debugs(3, DBG_CRITICAL, "FATAL: sslproxy_cert_adapt: setCommonName{" <<param << "} : using common name longer than 64 bytes is not supported");
+                self_destruct();
+                return;
+            }
+            ca->param = strdup(param);
+        }
+    } else {
+        debugs(3, DBG_CRITICAL, "FATAL: sslproxy_cert_adapt: unknown cert adaptation algorithm: " << al);
+        self_destruct();
+        return;
+    }
+
+    aclParseAclList(LegacyParser, &ca->aclList);
+
+    while (*cert_adapt)
+        cert_adapt = &(*cert_adapt)->next;
+
+    *cert_adapt = ca;
+}
+
+static void dump_sslproxy_cert_adapt(StoreEntry *entry, const char *name, sslproxy_cert_adapt *cert_adapt)
+{
+    for (sslproxy_cert_adapt *ca = cert_adapt; ca != NULL; ca = ca->next) {
+        storeAppendPrintf(entry, "%s ", name);
+        storeAppendPrintf(entry, "%s{%s} ", Ssl::sslCertAdaptAlgoritm(ca->alg), ca->param);
+        if (ca->aclList)
+            dump_acl_list(entry, ca->aclList);
+        storeAppendPrintf(entry, "\n");
+    }
+}
+
+static void free_sslproxy_cert_adapt(sslproxy_cert_adapt **cert_adapt)
+{
+    while (*cert_adapt) {
+        sslproxy_cert_adapt *ca = *cert_adapt;
+        *cert_adapt = ca->next;
+        safe_free(ca->param);
+
+        if (ca->aclList)
+            aclDestroyAclList(&ca->aclList);
+
+        safe_free(ca);
+    }
+}
+
+static void parse_sslproxy_cert_sign(sslproxy_cert_sign **cert_sign)
+{
+    char *al;
+    sslproxy_cert_sign *cs = (sslproxy_cert_sign *) xcalloc(1, sizeof(sslproxy_cert_sign));
+    if ((al = strtok(NULL, w_space)) == NULL) {
+        self_destruct();
+        return;
+    }
+
+    if (strcmp(al, Ssl::CertSignAlgorithmStr[Ssl::algSignTrusted]) == 0)
+        cs->alg = Ssl::algSignTrusted;
+    else if (strcmp(al, Ssl::CertSignAlgorithmStr[Ssl::algSignUntrusted]) == 0)
+        cs->alg = Ssl::algSignUntrusted;
+    else if (strcmp(al, Ssl::CertSignAlgorithmStr[Ssl::algSignSelf]) == 0)
+        cs->alg = Ssl::algSignSelf;
+    else {
+        debugs(3, DBG_CRITICAL, "FATAL: sslproxy_cert_sign: unknown cert signing algorithm: " << al);
+        self_destruct();
+        return;
+    }
+
+    aclParseAclList(LegacyParser, &cs->aclList);
+
+    while (*cert_sign)
+        cert_sign = &(*cert_sign)->next;
+
+    *cert_sign = cs;
+}
+
+static void dump_sslproxy_cert_sign(StoreEntry *entry, const char *name, sslproxy_cert_sign *cert_sign)
+{
+    sslproxy_cert_sign *cs;
+    for (cs = cert_sign; cs != NULL; cs = cs->next) {
+        storeAppendPrintf(entry, "%s ", name);
+        storeAppendPrintf(entry, "%s ", Ssl::certSignAlgorithm(cs->alg));
+        if (cs->aclList)
+            dump_acl_list(entry, cs->aclList);
+        storeAppendPrintf(entry, "\n");
+    }
+}
+
+static void free_sslproxy_cert_sign(sslproxy_cert_sign **cert_sign)
+{
+    while (*cert_sign) {
+        sslproxy_cert_sign *cs = *cert_sign;
+        *cert_sign = cs->next;
+
+        if (cs->aclList)
+            aclDestroyAclList(&cs->aclList);
+
+        safe_free(cs);
+    }
+}
+
+class sslBumpCfgRr: public ::RegisteredRunner
+{
+public:
+    static Ssl::BumpMode lastDeprecatedRule;
+    /* RegisteredRunner API */
+    virtual void run(const RunnerRegistry &);
+};
+
+Ssl::BumpMode sslBumpCfgRr::lastDeprecatedRule = Ssl::bumpEnd;
+
+RunnerRegistrationEntry(rrFinalizeConfig, sslBumpCfgRr);
+
+void sslBumpCfgRr::run(const RunnerRegistry &r)
+{
+    if (lastDeprecatedRule != Ssl::bumpEnd) {
+        assert( lastDeprecatedRule == Ssl::bumpClientFirst || lastDeprecatedRule == Ssl::bumpNone);
+        static char buf[1024];
+        if (lastDeprecatedRule == Ssl::bumpClientFirst) {
+            strcpy(buf, "ssl_bump deny all");
+            debugs(3, DBG_CRITICAL, "WARNING: auto-converting deprecated implicit "
+                   "\"ssl_bump deny all\" to \"ssl_bump none all\". New ssl_bump configurations "
+                   "must not use implicit rules. Update your ssl_bump rules.");
+        } else {
+            strcpy(buf, "ssl_bump allow all");
+            debugs(3, DBG_CRITICAL, "SECURITY NOTICE: auto-converting deprecated implicit "
+                   "\"ssl_bump allow all\" to \"ssl_bump client-first all\" which is usually "
+                   "inferior to the newer server-first bumping mode. New ssl_bump"
+                   " configurations must not use implicit rules. Update your ssl_bump rules.");
+        }
+        parse_line(buf);
+    }
+}
+
+static void parse_sslproxy_ssl_bump(acl_access **ssl_bump)
+{
+    typedef const char *BumpCfgStyle;
+    BumpCfgStyle bcsNone = NULL;
+    BumpCfgStyle bcsNew = "new client/server-first/none";
+    BumpCfgStyle bcsOld = "deprecated allow/deny";
+    static BumpCfgStyle bumpCfgStyleLast = bcsNone;
+    BumpCfgStyle bumpCfgStyleNow = bcsNone;
+    char *bm;
+    if ((bm = strtok(NULL, w_space)) == NULL) {
+        self_destruct();
+        return;
+    }
+
+    // if this is the first rule proccessed
+    if (*ssl_bump == NULL) {
+        bumpCfgStyleLast = bcsNone;
+        sslBumpCfgRr::lastDeprecatedRule = Ssl::bumpEnd;
+    }
+
+    acl_access *A = new acl_access;
+    A->allow = allow_t(ACCESS_ALLOWED);
+
+    if (strcmp(bm, Ssl::BumpModeStr[Ssl::bumpClientFirst]) == 0) {
+        A->allow.kind = Ssl::bumpClientFirst;
+        bumpCfgStyleNow = bcsNew;
+    } else if (strcmp(bm, Ssl::BumpModeStr[Ssl::bumpServerFirst]) == 0) {
+        A->allow.kind = Ssl::bumpServerFirst;
+        bumpCfgStyleNow = bcsNew;
+    } else if (strcmp(bm, Ssl::BumpModeStr[Ssl::bumpNone]) == 0) {
+        A->allow.kind = Ssl::bumpNone;
+        bumpCfgStyleNow = bcsNew;
+    } else if (strcmp(bm, "allow") == 0) {
+        debugs(3, DBG_CRITICAL, "SECURITY NOTICE: auto-converting deprecated "
+               "\"ssl_bump allow <acl>\" to \"ssl_bump client-first <acl>\" which "
+               "is usually inferior to the newer server-first "
+               "bumping mode. Update your ssl_bump rules.");
+        A->allow.kind = Ssl::bumpClientFirst;
+        bumpCfgStyleNow = bcsOld;
+        sslBumpCfgRr::lastDeprecatedRule = Ssl::bumpClientFirst;
+    } else if (strcmp(bm, "deny") == 0) {
+        debugs(3, DBG_CRITICAL, "WARNING: auto-converting deprecated "
+               "\"ssl_bump deny <acl>\" to \"ssl_bump none <acl>\". Update "
+               "your ssl_bump rules.");
+        A->allow.kind = Ssl::bumpNone;
+        bumpCfgStyleNow = bcsOld;
+        sslBumpCfgRr::lastDeprecatedRule = Ssl::bumpNone;
+    } else {
+        debugs(3, DBG_CRITICAL, "FATAL: unknown ssl_bump mode: " << bm);
+        self_destruct();
+        return;
+    }
+
+    if (bumpCfgStyleLast != bcsNone && bumpCfgStyleNow != bumpCfgStyleLast) {
+        debugs(3, DBG_CRITICAL, "FATAL: do not mix " << bumpCfgStyleNow << " actions with " <<
+               bumpCfgStyleLast << " actions. Update your ssl_bump rules.");
+        self_destruct();
+        return;
+    }
+
+    bumpCfgStyleLast = bumpCfgStyleNow;
+
+    aclParseAclList(LegacyParser, &A->aclList);
+
+    acl_access *B, **T;
+    for (B = *ssl_bump, T = ssl_bump; B; T = &B->next, B = B->next);
+    *T = A;
+}
+
+static void dump_sslproxy_ssl_bump(StoreEntry *entry, const char *name, acl_access *ssl_bump)
+{
+    acl_access *sb;
+    for (sb = ssl_bump; sb != NULL; sb = sb->next) {
+        storeAppendPrintf(entry, "%s ", name);
+        storeAppendPrintf(entry, "%s ", Ssl::bumpMode(sb->allow.kind));
+        if (sb->aclList)
+            dump_acl_list(entry, sb->aclList);
+        storeAppendPrintf(entry, "\n");
+    }
+}
+
+static void free_sslproxy_ssl_bump(acl_access **ssl_bump)
+{
+    free_acl_access(ssl_bump);
+}
 
 #endif
+
+static void dump_HeaderWithAclList(StoreEntry * entry, const char *name, HeaderWithAclList *headers)
+{
+    if (!headers)
+        return;
+
+    for (HeaderWithAclList::iterator hwa = headers->begin(); hwa != headers->end(); ++hwa) {
+        storeAppendPrintf(entry, "%s ", hwa->fieldName.c_str());
+        storeAppendPrintf(entry, "%s ", hwa->fieldValue.c_str());
+        if (hwa->aclList)
+            dump_acl_list(entry, hwa->aclList);
+        storeAppendPrintf(entry, "\n");
+    }
+}
+
+static void parse_HeaderWithAclList(HeaderWithAclList **headers)
+{
+    char *fn;
+    if (!*headers) {
+        *headers = new HeaderWithAclList;
+    }
+    if ((fn = strtok(NULL, w_space)) == NULL) {
+        self_destruct();
+        return;
+    }
+    HeaderWithAcl hwa;
+    hwa.fieldName = fn;
+    hwa.fieldId = httpHeaderIdByNameDef(fn, strlen(fn));
+    if (hwa.fieldId == HDR_BAD_HDR)
+        hwa.fieldId = HDR_OTHER;
+
+    String buf;
+    bool wasQuoted;
+    ConfigParser::ParseQuotedString(&buf, &wasQuoted);
+    hwa.fieldValue = buf.termedBuf();
+    hwa.quoted = wasQuoted;
+    if (hwa.quoted) {
+        Format::Format *nlf =  new ::Format::Format("hdrWithAcl");
+        if (!nlf->parse(hwa.fieldValue.c_str())) {
+            self_destruct();
+            return;
+        }
+        hwa.valueFormat = nlf;
+    }
+    aclParseAclList(LegacyParser, &hwa.aclList);
+    (*headers)->push_back(hwa);
+}
+
+static void free_HeaderWithAclList(HeaderWithAclList **header)
+{
+    if (!(*header))
+        return;
+
+    for (HeaderWithAclList::iterator hwa = (*header)->begin(); hwa != (*header)->end(); ++hwa) {
+        if (hwa->aclList)
+            aclDestroyAclList(&hwa->aclList);
+
+        if (hwa->valueFormat) {
+            delete hwa->valueFormat;
+            hwa->valueFormat = NULL;
+        }
+    }
+    delete *header;
+    *header = NULL;
+}
