void
Security::PeerOptions::updateContextNpn(Security::ContextPointer &ctx)
{
    if (!flags.tlsNpn)
        return;

#if USE_OPENSSL && defined(TLSEXT_TYPE_next_proto_neg)
    SSL_CTX_set_next_proto_select_cb(ctx.get(), &ssl_next_proto_cb, nullptr);
#endif

    // NOTE: GnuTLS does not support the obsolete NPN extension.
    //       it does support ALPN per-session, not per-context.
}