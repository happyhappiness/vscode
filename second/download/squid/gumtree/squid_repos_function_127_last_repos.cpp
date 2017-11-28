ssize_t
Transport::Write(void *buf, size_t len)
{
    if (conn < 0)
        return -1;

    if (Config.tlsEnabled) {
#if USE_GNUTLS
        gnutls_record_send(Config.session, buf, len);
        return len;
#else
        return 0;
#endif
    } else {

#if _SQUID_WINDOWS_
        return send(conn, buf, len, 0);
#else
        alarm(Config.ioTimeout);
        return write(conn, buf, len);
#endif
    }
}