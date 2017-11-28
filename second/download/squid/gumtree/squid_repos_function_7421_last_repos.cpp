static int
tls_write_method(int fd, const char *buf, int len)
{
    auto session = fd_table[fd].ssl.get();
    debugs(83, 3, "started for session=" << (void*)session);

#if USE_OPENSSL
    if (!SSL_is_init_finished(session)) {
        errno = ENOTCONN;
        return -1;
    }
#endif

#if USE_OPENSSL
    int i = SSL_write(session, buf, len);
#elif USE_GNUTLS
    int i = gnutls_record_send(session, buf, len);
#endif

    if (i > 0) {
        debugs(83, 8, "TLS FD " << fd << " session=" << (void*)session << " " << i << " bytes");
    }
    return i;
}