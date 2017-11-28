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