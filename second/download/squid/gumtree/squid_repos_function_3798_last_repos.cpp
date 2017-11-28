int Ssl::Bio::write(const char *buf, int size, BIO *table)
{
    errno = 0;
#if _SQUID_WINDOWS_
    const int result = socket_write_method(fd_, buf, size);
#else
    const int result = default_write_method(fd_, buf, size);
#endif
    const int xerrno = errno;
    debugs(83, 5, "FD " << fd_ << " wrote " << result << " <= " << size);

    BIO_clear_retry_flags(table);
    if (result < 0) {
        const bool ignoreError = ignoreErrno(xerrno) != 0;
        debugs(83, 5, "error: " << xerrno << " ignored: " << ignoreError);
        if (ignoreError)
            BIO_set_retry_write(table);
    }

    return result;
}