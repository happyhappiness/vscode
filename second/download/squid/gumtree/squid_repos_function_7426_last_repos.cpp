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