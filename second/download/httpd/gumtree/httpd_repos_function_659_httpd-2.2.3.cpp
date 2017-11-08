int modssl_session_get_time(SSL_SESSION *session)
{
#ifdef OPENSSL_VERSION_NUMBER
    return SSL_SESSION_get_time(session);
#else /* assume sslc */
    CRYPTO_TIME_T ct;
    SSL_SESSION_get_time(session, &ct);
    return CRYPTO_time_to_int(&ct);
#endif
}