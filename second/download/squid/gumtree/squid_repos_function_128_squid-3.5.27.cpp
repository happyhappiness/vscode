ssize_t
Transport::Read(void *buf, size_t len)
{
    if (conn < 0)
        return -1;

    if (Config.tlsEnabled) {
#if USE_GNUTLS
        return gnutls_record_recv(Config.session, buf, len);
#else
        return 0;
#endif
    } else {

#if _SQUID_WINDOWS_
        return recv(conn, buf, len, 0);
#else
        alarm(Config.ioTimeout);
        return read(conn, buf, len);
#endif
    }
}