 
     dlinkDelete(&entry->lru, &def->lru_list);
     ExternalACLEntry *e = const_cast<ExternalACLEntry *>(entry.getRaw()); // XXX: make hash a std::map of Pointer.
     dlinkAdd(e, &entry->lru, &def->lru_list);
 }
 
-#if USE_OPENSSL
-static const char *
-external_acl_ssl_get_user_attribute(const ACLFilledChecklist &ch, const char *attr)
-{
-    if (ch.conn() != NULL && Comm::IsConnOpen(ch.conn()->clientConnection)) {
-        if (SSL *ssl = fd_table[ch.conn()->clientConnection->fd].ssl)
-            return sslGetUserAttribute(ssl, attr);
-    }
-    return NULL;
-}
-#endif
-
 static char *
 makeExternalAclKey(ACLFilledChecklist * ch, external_acl_data * acl_data)
 {
     static MemBuf mb;
-    char buf[256];
-    int first = 1;
-    wordlist *arg;
-    HttpRequest *request = ch->request;
-    HttpReply *reply = ch->reply;
     mb.reset();
-    bool data_used = false;
-
-    for (external_acl_format::Pointer format = acl_data->def->format; format != NULL; format = format->next) {
-        const char *str = NULL;
-        String sb;
-
-        switch (format->type) {
-#if USE_AUTH
-        case Format::LFT_USER_LOGIN:
-            // if this ACL line was the cause of credentials fetch
-            // they may not already be in the checklist
-            if (ch->auth_user_request == NULL && ch->request)
-                ch->auth_user_request = ch->request->auth_user_request;
-
-            if (ch->auth_user_request != NULL)
-                str = ch->auth_user_request->username();
-            break;
-#endif
-#if USE_IDENT
-        case Format::LFT_USER_IDENT:
-            str = ch->rfc931;
-
-            if (!str || !*str) {
-                // if we fail to go async, we still return NULL and the caller
-                // will detect the failure in ACLExternal::match().
-                (void)ch->goAsync(IdentLookup::Instance());
-                return NULL;
-            }
-
-            break;
-#endif
-
-        case Format::LFT_CLIENT_IP_ADDRESS:
-            str = ch->src_addr.toStr(buf,sizeof(buf));
-            break;
-
-        case Format::LFT_CLIENT_PORT:
-            snprintf(buf, sizeof(buf), "%d", request->client_addr.port());
-            str = buf;
-            break;
-
-#if USE_SQUID_EUI
-        case Format::LFT_CLIENT_EUI:
-            // TODO make the ACL checklist have a direct link to any TCP details.
-            if (request->clientConnectionManager.valid() && request->clientConnectionManager->clientConnection != NULL)
-            {
-                if (request->clientConnectionManager->clientConnection->remote.isIPv4())
-                    request->clientConnectionManager->clientConnection->remoteEui48.encode(buf, sizeof(buf));
-                else
-                    request->clientConnectionManager->clientConnection->remoteEui64.encode(buf, sizeof(buf));
-                str = buf;
-            }
-            break;
-
-        case Format::LFT_EXT_ACL_CLIENT_EUI48:
-            if (request->clientConnectionManager.valid() && request->clientConnectionManager->clientConnection != NULL &&
-                    request->clientConnectionManager->clientConnection->remoteEui48.encode(buf, sizeof(buf)))
-                str = buf;
-            break;
-
-        case Format::LFT_EXT_ACL_CLIENT_EUI64:
-            if (request->clientConnectionManager.valid() && request->clientConnectionManager->clientConnection != NULL &&
-                    request->clientConnectionManager->clientConnection->remoteEui64.encode(buf, sizeof(buf)))
-                str = buf;
-            break;
-#endif
-
-        case Format::LFT_LOCAL_LISTENING_IP:
-            str = request->my_addr.toStr(buf, sizeof(buf));
-            break;
-
-        case Format::LFT_LOCAL_LISTENING_PORT:
-            snprintf(buf, sizeof(buf), "%d", request->my_addr.port());
-            str = buf;
-            break;
-
-        case Format::LFT_CLIENT_REQ_URI:
-            str = urlCanonical(request);
-            break;
-
-        case Format::LFT_CLIENT_REQ_URLDOMAIN:
-            str = request->GetHost();
-            break;
-
-        case Format::LFT_CLIENT_REQ_URLSCHEME:
-            str = request->url.getScheme().c_str();
-            break;
-
-        case Format::LFT_CLIENT_REQ_URLPORT:
-            snprintf(buf, sizeof(buf), "%d", request->port);
-            str = buf;
-            break;
-
-        case Format::LFT_CLIENT_REQ_URLPATH:
-            str = request->urlpath.termedBuf();
-            break;
-
-        case Format::LFT_CLIENT_REQ_METHOD: {
-            const SBuf &s = request->method.image();
-            sb.append(s.rawContent(), s.length());
-        }
-        str = sb.termedBuf();
-        break;
-
-        case Format::LFT_ADAPTED_REQUEST_HEADER:
-            if (format->header_id == -1)
-                sb = request->header.getByName(format->header);
-            else
-                sb = request->header.getStrOrList(format->header_id);
-            str = sb.termedBuf();
-            break;
-
-        case Format::LFT_ADAPTED_REQUEST_HEADER_ELEM:
-            if (format->header_id == -1)
-                sb = request->header.getByNameListMember(format->header, format->member, format->separator);
-            else
-                sb = request->header.getListMember(format->header_id, format->member, format->separator);
-            str = sb.termedBuf();
-            break;
-
-        case Format::LFT_REPLY_HEADER:
-            if (reply) {
-                if (format->header_id == -1)
-                    sb = reply->header.getByName(format->header);
-                else
-                    sb = reply->header.getStrOrList(format->header_id);
-                str = sb.termedBuf();
-            }
-            break;
-
-        case Format::LFT_REPLY_HEADER_ELEM:
-            if (reply) {
-                if (format->header_id == -1)
-                    sb = reply->header.getByNameListMember(format->header, format->member, format->separator);
-                else
-                    sb = reply->header.getListMember(format->header_id, format->member, format->separator);
-                str = sb.termedBuf();
-            }
-            break;
-
-#if USE_OPENSSL
-
-        case Format::LFT_EXT_ACL_USER_CERT_RAW:
-
-            if (ch->conn() != NULL && Comm::IsConnOpen(ch->conn()->clientConnection)) {
-                SSL *ssl = fd_table[ch->conn()->clientConnection->fd].ssl;
-
-                if (ssl)
-                    str = sslGetUserCertificatePEM(ssl);
-            }
-
-            break;
-
-        case Format::LFT_EXT_ACL_USER_CERTCHAIN_RAW:
-
-            if (ch->conn() != NULL && Comm::IsConnOpen(ch->conn()->clientConnection)) {
-                SSL *ssl = fd_table[ch->conn()->clientConnection->fd].ssl;
-
-                if (ssl)
-                    str = sslGetUserCertificateChainPEM(ssl);
-            }
-
-            break;
-
-        case Format::LFT_EXT_ACL_USER_CERT:
-            str = external_acl_ssl_get_user_attribute(*ch, format->header);
-            break;
-
-        case Format::LFT_EXT_ACL_USER_CA_CERT:
-
-            if (ch->conn() != NULL && Comm::IsConnOpen(ch->conn()->clientConnection)) {
-                SSL *ssl = fd_table[ch->conn()->clientConnection->fd].ssl;
-
-                if (ssl)
-                    str = sslGetCAAttribute(ssl, format->header);
-            }
-
-            break;
 
-        case Format::LFT_SSL_CLIENT_SNI:
-            if (ch->conn() != NULL) {
-                if (Ssl::ServerBump * srvBump = ch->conn()->serverBump()) {
-                    if (!srvBump->clientSni.isEmpty())
-                        str = srvBump->clientSni.c_str();
-                }
-            }
-            break;
+    // check for special case tokens in the format
+    for (Format::Token *t = acl_data->def->format.format; t ; t = t->next) {
 
-        case Format::LFT_SSL_SERVER_CERT_SUBJECT:
-        case Format::LFT_SSL_SERVER_CERT_ISSUER: {
-            X509 *serverCert = NULL;
-            if (ch->serverCert.get())
-                serverCert = ch->serverCert.get();
-            else if (ch->conn() && ch->conn()->serverBump())
-                serverCert = ch->conn()->serverBump()->serverCert.get();
-
-            if (serverCert) {
-                if (format->type == Format::LFT_SSL_SERVER_CERT_SUBJECT)
-                    str = Ssl::GetX509UserAttribute(serverCert, "DN");
-                else
-                    str = Ssl::GetX509CAAttribute(serverCert, "DN");
-            }
-            break;
+        if (t->type == Format::LFT_EXT_ACL_NAME) {
+            // setup for %ACL
+            safe_free(ch->al->lastAclName);
+            ch->al->lastAclName = xstrdup(acl_data->name);
         }
 
-#endif
-#if USE_AUTH
-        case Format::LFT_USER_EXTERNAL:
-            str = request->extacl_user.termedBuf();
-            break;
-#endif
-        case Format::LFT_USER_NAME:
-            /* find the first available name from various sources */
-#if USE_AUTH
-            // if this ACL line was the cause of credentials fetch
-            // they may not already be in the checklist
-            if (!ch->auth_user_request && ch->request)
-                ch->auth_user_request = ch->request->auth_user_request;
-
-            if (ch->auth_user_request != NULL)
-                str = ch->auth_user_request->username();
-
-            if ((!str || !*str) &&
-                    (request->extacl_user.size() > 0 && request->extacl_user[0] != '-'))
-                str = request->extacl_user.termedBuf();
-#endif
-#if USE_OPENSSL
-            if (!str || !*str)
-                str = external_acl_ssl_get_user_attribute(*ch, "CN");
-#endif
-#if USE_IDENT
-            if (!str || !*str)
-                str = ch->rfc931;
-#endif
-            break;
-        case Format::LFT_EXT_LOG:
-            str = request->extacl_log.termedBuf();
-            break;
-        case Format::LFT_TAG:
-            str = request->tag.termedBuf();
-            break;
-        case Format::LFT_EXT_ACL_NAME:
-            str = acl_data->name;
-            break;
-        case Format::LFT_EXT_ACL_DATA:
-            data_used = true;
-            for (arg = acl_data->arguments; arg; arg = arg->next) {
-                if (!first)
+        if (t->type == Format::LFT_EXT_ACL_DATA) {
+            // setup string for %DATA
+            SBuf sb;
+            for (auto arg = acl_data->arguments; arg; arg = arg->next) {
+                if (sb.length())
                     sb.append(" ", 1);
 
-                if (acl_data->def->quote == external_acl::QUOTE_METHOD_URL) {
+                if (acl_data->def->quote == Format::LOG_QUOTE_URL) {
                     const char *quoted = rfc1738_escape(arg->key);
                     sb.append(quoted, strlen(quoted));
                 } else {
                     static MemBuf mb2;
                     mb2.init();
                     strwordquote(&mb2, arg->key);
                     sb.append(mb2.buf, mb2.size);
                     mb2.clean();
                 }
-
-                first = 0;
             }
-            break;
-        case Format::LFT_PERCENT:
-            str = "%";
-            break;
 
-        default:
-            // TODO: replace this function with Format::assemble()
-            // For now die on unsupported logformat codes.
-            fatalf("ERROR: unknown external_acl_type format %u", (uint8_t)format->type);
-            break;
-        }
-
-        if (str)
-            if (!*str)
-                str = NULL;
-
-        if (!str)
-            str = "-";
-
-        if (!first)
-            mb.append(" ", 1);
-
-        if (acl_data->def->quote == external_acl::QUOTE_METHOD_URL) {
-            const char *quoted = rfc1738_escape(str);
-            mb.append(quoted, strlen(quoted));
-        } else {
-            strwordquote(&mb, str);
+            ch->al->lastAclData = sb;
         }
 
-        sb.clean();
-
-        first = 0;
-    }
-
-    if (!data_used) {
-        for (arg = acl_data->arguments; arg; arg = arg->next) {
-            if (!first)
-                mb.append(" ", 1);
-
-            if (acl_data->def->quote == external_acl::QUOTE_METHOD_URL) {
-                const char *quoted = rfc1738_escape(arg->key);
-                mb.append(quoted, strlen(quoted));
-            } else {
-                strwordquote(&mb, arg->key);
+#if USE_IDENT
+        if (t->type == Format::LFT_USER_IDENT) {
+            if (!*ch->rfc931) {
+                // if we fail to go async, we still return NULL and the caller
+                // will detect the failure in ACLExternal::match().
+                (void)ch->goAsync(IdentLookup::Instance());
+                return NULL;
             }
-
-            first = 0;
         }
+#endif
     }
 
+    // assemble the full helper lookup string
+    acl_data->def->format.assemble(mb, ch->al, 0);
+
     return mb.buf;
 }
 
 static int
 external_acl_entry_expired(external_acl * def, const ExternalACLEntryPointer &entry)
 {
