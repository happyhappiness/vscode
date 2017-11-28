inline const char *ErrorString(const ErrorCode code) {
#if USE_OPENSSL
    return ERR_error_string(code, nullptr);
#elif USE_GNUTLS
    return gnutls_strerror(code);
#else
    return "[no TLS library]";
#endif
}