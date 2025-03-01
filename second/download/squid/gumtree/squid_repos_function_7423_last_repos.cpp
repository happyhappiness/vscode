static bool
CreateSession(const Security::ContextPointer &ctx, const Comm::ConnectionPointer &conn, Security::Io::Type type, const char *squidCtx)
{
    if (!Comm::IsConnOpen(conn)) {
        debugs(83, DBG_IMPORTANT, "Gone connection");
        return false;
    }

#if USE_OPENSSL || USE_GNUTLS

    const char *errAction = "with no TLS/SSL library";
    int errCode = 0;
#if USE_OPENSSL
    Security::SessionPointer session(Security::NewSessionObject(ctx));
    if (!session) {
        errCode = ERR_get_error();
        errAction = "failed to allocate handle";
    }
#elif USE_GNUTLS
    gnutls_session_t tmp;
    errCode = gnutls_init(&tmp, static_cast<unsigned int>(type) | GNUTLS_NONBLOCK);
    Security::SessionPointer session(tmp, [](gnutls_session_t p) {
        debugs(83, 5, "gnutls_deinit session=" << (void*)p);
        gnutls_deinit(p);
    });
    debugs(83, 5, "gnutls_init " << (type == Security::Io::BIO_TO_SERVER ? "client" : "server" )<< " session=" << (void*)session.get());
    if (errCode != GNUTLS_E_SUCCESS) {
        session.reset();
        errAction = "failed to initialize session";
    }
#endif

    if (session) {
        const int fd = conn->fd;

#if USE_OPENSSL
        // without BIO, we would call SSL_set_fd(ssl.get(), fd) instead
        if (BIO *bio = Ssl::Bio::Create(fd, type)) {
            Ssl::Bio::Link(session.get(), bio); // cannot fail
#elif USE_GNUTLS
        errCode = gnutls_credentials_set(session.get(), GNUTLS_CRD_CERTIFICATE, ctx.get());
        if (errCode == GNUTLS_E_SUCCESS) {

            if (auto *peer = conn->getPeer())
                peer->secure.updateSessionOptions(session);
            else
                Security::ProxyOutgoingConfig.updateSessionOptions(session);

            // NP: GnuTLS does not yet support the BIO operations
            //     this does the equivalent of SSL_set_fd() for now.
            gnutls_transport_set_int(session.get(), fd);
            gnutls_handshake_set_timeout(session.get(), GNUTLS_DEFAULT_HANDSHAKE_TIMEOUT);
#endif

            debugs(83, 5, "link FD " << fd << " to TLS session=" << (void*)session.get());
            fd_table[fd].ssl = session;
            fd_table[fd].read_method = &tls_read_method;
            fd_table[fd].write_method = &tls_write_method;
            fd_note(fd, squidCtx);
            return true;
        }

#if USE_OPENSSL
        errCode = ERR_get_error();
        errAction = "failed to initialize I/O";
#elif USE_GNUTLS
        errAction = "failed to assign credentials";
#endif
    }

    debugs(83, DBG_IMPORTANT, "ERROR: " << squidCtx << ' ' << errAction <<
           ": " << (errCode != 0 ? Security::ErrorString(errCode) : ""));
#endif
    return false;
}

bool
Security::CreateClientSession(const Security::ContextPointer &ctx, const Comm::ConnectionPointer &c, const char *squidCtx)
{
    return CreateSession(ctx, c, Security::Io::BIO_TO_SERVER, squidCtx);
}

bool
Security::CreateServerSession(const Security::ContextPointer &ctx, const Comm::ConnectionPointer &c, const char *squidCtx)
{
    return CreateSession(ctx, c, Security::Io::BIO_TO_CLIENT, squidCtx);
}

void
Security::SessionSendGoodbye(const Security::SessionPointer &s)
{
    debugs(83, 5, "session=" << (void*)s.get());
    if (s) {
#if USE_OPENSSL
        SSL_shutdown(s.get());
#elif USE_GNUTLS
        gnutls_bye(s.get(), GNUTLS_SHUT_RDWR);
#endif
    }
}

bool
Security::SessionIsResumed(const Security::SessionPointer &s)
{
    bool result = false;
#if USE_OPENSSL
    result = SSL_session_reused(s.get()) == 1;
#elif USE_GNUTLS
    result = gnutls_session_is_resumed(s.get()) != 0;
#endif
    debugs(83, 7, "session=" << (void*)s.get() << ", query? answer: " << (result ? 'T' : 'F') );
    return result;
}

void
Security::MaybeGetSessionResumeData(const Security::SessionPointer &s, Security::SessionStatePointer &data)
{
    if (!SessionIsResumed(s)) {
#if USE_OPENSSL
        // nil is valid for SSL_get1_session(), it cannot fail.
        data.reset(SSL_get1_session(s.get()));
#elif USE_GNUTLS
        gnutls_datum_t *tmp = nullptr;
        const auto x = gnutls_session_get_data2(s.get(), tmp);
        if (x != GNUTLS_E_SUCCESS) {
            debugs(83, 3, "session=" << (void*)s.get() << " error: " << Security::ErrorString(x));
        }
        data.reset(tmp);
#endif
        debugs(83, 5, "session=" << (void*)s.get() << " data=" << (void*)data.get());
    } else {
        debugs(83, 5, "session=" << (void*)s.get() << " data=" << (void*)data.get() << ", do nothing.");
    }
}

void
Security::SetSessionResumeData(const Security::SessionPointer &s, const Security::SessionStatePointer &data)
{
    if (data) {
#if USE_OPENSSL
        if (!SSL_set_session(s.get(), data.get())) {
            const auto ssl_error = ERR_get_error();
            debugs(83, 3, "session=" << (void*)s.get() << " data=" << (void*)data.get() <<
                   " resume error: " << Security::ErrorString(ssl_error));
        }
#elif USE_GNUTLS
        const auto x = gnutls_session_set_data(s.get(), data->data, data->size);
        if (x != GNUTLS_E_SUCCESS) {
            debugs(83, 3, "session=" << (void*)s.get() << " data=" << (void*)data.get() <<
                   " resume error: " << Security::ErrorString(x));
        }
#else
        // critical because, how did it get here?
        debugs(83, DBG_CRITICAL, "no TLS library. session=" << (void*)s.get() << " data=" << (void*)data.get());
#endif
        debugs(83, 5, "session=" << (void*)s.get() << " data=" << (void*)data.get());
    } else {
        debugs(83, 5, "session=" << (void*)s.get() << " no resume data");
    }
}

static bool
isTlsServer()
{
    for (AnyP::PortCfgPointer s = HttpPortList; s != nullptr; s = s->next) {
        if (s->secure.encryptTransport)
            return true;
        if (s->flags.tunnelSslBumping)
            return true;
    }

    return false;
}

#if USE_OPENSSL
static int
store_session_cb(SSL *ssl, SSL_SESSION *session)
{
    if (!SessionCache)
        return 0;

    debugs(83, 5, "Request to store SSL_SESSION");

    SSL_SESSION_set_timeout(session, Config.SSL.session_ttl);

#if HAVE_LIBSSL_SSL_SESSION_GET_ID
    unsigned int idlen;
    const unsigned char *id = SSL_SESSION_get_id(session, &idlen);
#else
    unsigned char *id = session->session_id;
    unsigned int idlen = session->session_id_length;
#endif
    // XXX: the other calls [to openForReading()] do not copy the sessionId to a char buffer, does this really have to?
    unsigned char key[MEMMAP_SLOT_KEY_SIZE];
    // Session ids are of size 32bytes. They should always fit to a
    // MemMap::Slot::key
    assert(idlen <= MEMMAP_SLOT_KEY_SIZE);
    memset(key, 0, sizeof(key));
    memcpy(key, id, idlen);
    int pos;
    if (auto slotW = SessionCache->openForWriting(static_cast<const cache_key*>(key), pos)) {
        int lenRequired = i2d_SSL_SESSION(session, nullptr);
        if (lenRequired <  MEMMAP_SLOT_DATA_SIZE) {
            unsigned char *p = static_cast<unsigned char *>(slotW->p);
            lenRequired = i2d_SSL_SESSION(session, &p);
            slotW->set(key, nullptr, lenRequired, squid_curtime + Config.SSL.session_ttl);
        }
        SessionCache->closeForWriting(pos);
        debugs(83, 5, "wrote an SSL_SESSION entry of size " << lenRequired << " at pos " << pos);
    }
    return 0;
}

static void
remove_session_cb(SSL_CTX *, SSL_SESSION *sessionID)
{
    if (!SessionCache)
        return;

    debugs(83, 5, "Request to remove corrupted or not valid SSL_SESSION");
    int pos;
    if (SessionCache->openForReading(reinterpret_cast<const cache_key*>(sessionID), pos)) {
        SessionCache->closeForReading(pos);
        // TODO:
        // What if we are not able to remove the session?
        // Maybe schedule a job to remove it later?
        // For now we just have an invalid entry in cache until will be expired
        // The OpenSSL library will reject it when we try to use it
        SessionCache->free(pos);
    }
}

static SSL_SESSION *
#if SQUID_USE_CONST_SSL_SESSION_CBID
get_session_cb(SSL *, const unsigned char *sessionID, int len, int *copy)
#else
get_session_cb(SSL *, unsigned char *sessionID, int len, int *copy)
#endif
{
    if (!SessionCache)
        return nullptr;

    const unsigned int *p = reinterpret_cast<const unsigned int *>(sessionID);
    debugs(83, 5, "Request to search for SSL_SESSION of len: " <<
           len << p[0] << ":" << p[1]);

    SSL_SESSION *session = nullptr;
    int pos;
    if (const auto slot = SessionCache->openForReading(static_cast<const cache_key*>(sessionID), pos)) {
        if (slot->expire > squid_curtime) {
            const unsigned char *ptr = slot->p;
            session = d2i_SSL_SESSION(nullptr, &ptr, slot->pSize);
            debugs(83, 5, "SSL_SESSION retrieved from cache at pos " << pos);
        } else
            debugs(83, 5, "SSL_SESSION in cache expired");
        SessionCache->closeForReading(pos);
    }

    if (!session)
        debugs(83, 5, "Failed to retrieve SSL_SESSION from cache\n");

    // With the parameter copy the callback can require the SSL engine
    // to increment the reference count of the SSL_SESSION object, Normally
    // the reference count is not incremented and therefore the session must
    // not be explicitly freed with SSL_SESSION_free(3).
    *copy = 0;
    return session;
}