     if (ssl_crtd->stats.queue_size >= (int)(ssl_crtd->childs.n_running * 2)) {
         if (first_warn == 0)
             first_warn = squid_curtime;
         if (squid_curtime - first_warn > 3 * 60)
             fatal("SSL servers not responding for 3 minutes");
         debugs(34, DBG_IMPORTANT, HERE << "Queue overload, rejecting");
-        callback(data, (char *)"error 45 Temporary network problem, please retry later");
+        HelperReply failReply;
+        failReply.result = HelperReply::BrokenHelper;
+        failReply.notes.add("message", "error 45 Temporary network problem, please retry later");
+        callback(data, failReply);
         return;
     }
 
     first_warn = 0;
     std::string msg = message.compose();
     msg += '\n';
     helperSubmit(ssl_crtd, msg.c_str(), callback, data);
 }
+#endif //USE_SSL_CRTD
+
+Ssl::CertValidationHelper * Ssl::CertValidationHelper::GetInstance()
+{
+    static Ssl::CertValidationHelper sslHelper;
+    if (!Ssl::TheConfig.ssl_crt_validator)
+        return NULL;
+    return &sslHelper;
+}
+
+Ssl::CertValidationHelper::CertValidationHelper() : ssl_crt_validator(NULL)
+{
+}
+
+Ssl::CertValidationHelper::~CertValidationHelper()
+{
+    Shutdown();
+}
+
+void Ssl::CertValidationHelper::Init()
+{
+    assert(ssl_crt_validator == NULL);
+
+    // we need to start ssl_crtd only if some port(s) need to bump SSL
+    bool found = false;
+    for (AnyP::PortCfg *s = ::Config.Sockaddr.http; !found && s; s = s->next)
+        found = s->flags.tunnelSslBumping;
+    for (AnyP::PortCfg *s = ::Config.Sockaddr.https; !found && s; s = s->next)
+        found = s->flags.tunnelSslBumping;
+    if (!found)
+        return;
+
+    ssl_crt_validator = new helper("ssl_crt_validator");
+    ssl_crt_validator->childs.updateLimits(Ssl::TheConfig.ssl_crt_validator_Children);
+    ssl_crt_validator->ipc_type = IPC_STREAM;
+    // The crtd messages may contain the eol ('\n') character. We are
+    // going to use the '\1' char as the end-of-message mark.
+    ssl_crt_validator->eom = '\1';
+    assert(ssl_crt_validator->cmdline == NULL);
+
+    int ttl = 60;
+    size_t cache = 2048;
+    {
+        char *tmp = xstrdup(Ssl::TheConfig.ssl_crt_validator);
+        char *tmp_begin = tmp;
+        char * token = NULL;
+        bool parseParams = true;
+        while ((token = strwordtok(NULL, &tmp))) {
+            if (parseParams) {
+                if (strncmp(token, "ttl=", 4) == 0) {
+                    ttl = atoi(token + 4);
+                    continue;
+                } else if (strncmp(token, "cache=", 6) == 0) {
+                    cache = atoi(token + 6);
+                    continue;
+                } else
+                    parseParams = false;
+            }
+            wordlistAdd(&ssl_crt_validator->cmdline, token);
+        }
+        xfree(tmp_begin);
+    }
+    helperOpenServers(ssl_crt_validator);
+
+    //WARNING: initializing static member in an object initialization method
+    assert(HelperCache == NULL);
+    HelperCache = new LruMap<Ssl::CertValidationResponse>(ttl, cache);
+}
+
+void Ssl::CertValidationHelper::Shutdown()
+{
+    if (!ssl_crt_validator)
+        return;
+    helperShutdown(ssl_crt_validator);
+    wordlistDestroy(&ssl_crt_validator->cmdline);
+    delete ssl_crt_validator;
+    ssl_crt_validator = NULL;
+
+    // CertValidationHelper::HelperCache is a static member, it is not good policy to
+    // reset it here. Will work because the current Ssl::CertValidationHelper is
+    // always the same static object.
+    delete HelperCache;
+    HelperCache = NULL;
+}
+
+struct submitData {
+    std::string query;
+    Ssl::CertValidationHelper::CVHCB *callback;
+    void *data;
+    SSL *ssl;
+    CBDATA_CLASS2(submitData);
+};
+CBDATA_CLASS_INIT(submitData);
+
+static void
+sslCrtvdHandleReplyWrapper(void *data, const HelperReply &reply)
+{
+    Ssl::CertValidationMsg replyMsg(Ssl::CrtdMessage::REPLY);
+    Ssl::CertValidationResponse *validationResponse = new Ssl::CertValidationResponse;
+    std::string error;
+
+    submitData *crtdvdData = static_cast<submitData *>(data);
+    STACK_OF(X509) *peerCerts = SSL_get_peer_cert_chain(crtdvdData->ssl);
+    if (reply.result == HelperReply::BrokenHelper) {
+        debugs(83, DBG_IMPORTANT, "\"ssl_crtvd\" helper error response: " << reply.other().content());
+        validationResponse->resultCode = HelperReply::BrokenHelper;
+    } else if (replyMsg.parse(reply.other().content(), reply.other().contentSize()) != Ssl::CrtdMessage::OK ||
+               !replyMsg.parseResponse(*validationResponse, peerCerts, error) ) {
+        debugs(83, DBG_IMPORTANT, "WARNING: Reply from ssl_crtvd for " << " is incorrect");
+        debugs(83, DBG_IMPORTANT, "Certificate cannot be validated. ssl_crtvd response: " << replyMsg.getBody());
+        validationResponse->resultCode = HelperReply::BrokenHelper;
+    } else
+        validationResponse->resultCode = reply.result;
+
+    crtdvdData->callback(crtdvdData->data, *validationResponse);
+
+    if (Ssl::CertValidationHelper::HelperCache &&
+            (validationResponse->resultCode == HelperReply::Okay || validationResponse->resultCode == HelperReply::Error)) {
+        Ssl::CertValidationHelper::HelperCache->add(crtdvdData->query.c_str(), validationResponse);
+    } else
+        delete validationResponse;
+
+    cbdataReferenceDone(crtdvdData->data);
+    SSL_free(crtdvdData->ssl);
+    delete crtdvdData;
+}
+
+void Ssl::CertValidationHelper::sslSubmit(Ssl::CertValidationRequest const &request, Ssl::CertValidationHelper::CVHCB * callback, void * data)
+{
+    static time_t first_warn = 0;
+    assert(ssl_crt_validator);
+
+    if (ssl_crt_validator->stats.queue_size >= (int)(ssl_crt_validator->childs.n_running * 2)) {
+        if (first_warn == 0)
+            first_warn = squid_curtime;
+        if (squid_curtime - first_warn > 3 * 60)
+            fatal("ssl_crtvd queue being overloaded for long time");
+        debugs(83, DBG_IMPORTANT, "WARNING: ssl_crtvd queue overload, rejecting");
+        Ssl::CertValidationResponse resp;
+        resp.resultCode = HelperReply::BrokenHelper;
+        callback(data, resp);
+        return;
+    }
+    first_warn = 0;
+
+    Ssl::CertValidationMsg message(Ssl::CrtdMessage::REQUEST);
+    message.setCode(Ssl::CertValidationMsg::code_cert_validate);
+    message.composeRequest(request);
+    debugs(83, 5, "SSL crtvd request: " << message.compose().c_str());
+
+    submitData *crtdvdData = new submitData;
+    crtdvdData->query = message.compose();
+    crtdvdData->query += '\n';
+    crtdvdData->callback = callback;
+    crtdvdData->data = cbdataReference(data);
+    crtdvdData->ssl = request.ssl;
+    CRYPTO_add(&crtdvdData->ssl->references,1,CRYPTO_LOCK_SSL);
+    Ssl::CertValidationResponse const*validationResponse;
+
+    if (CertValidationHelper::HelperCache &&
+            (validationResponse = CertValidationHelper::HelperCache->get(crtdvdData->query.c_str()))) {
+        callback(data, *validationResponse);
+        cbdataReferenceDone(crtdvdData->data);
+        SSL_free(crtdvdData->ssl);
+        delete crtdvdData;
+        return;
+    }
+    helperSubmit(ssl_crt_validator, crtdvdData->query.c_str(), sslCrtvdHandleReplyWrapper, crtdvdData);
+}
