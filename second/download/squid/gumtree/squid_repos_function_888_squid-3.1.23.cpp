void
comm_close_complete(int fd, void *data)
{
#if USE_SSL
    fde *F = &fd_table[fd];

    if (F->ssl) {
        SSL_free(F->ssl);
        F->ssl = NULL;
    }

    if (F->dynamicSslContext) {
        SSL_CTX_free(F->dynamicSslContext);
        F->dynamicSslContext = NULL;
    }
#endif
    fd_close(fd);		/* update fdstat */

    close(fd);

    fdc_table[fd] = AcceptFD(fd);

    statCounter.syscalls.sock.closes++;

    /* When an fd closes, give accept() a chance, if need be */

    if (fdNFree() >= RESERVED_FD)
        AcceptLimiter::Instance().kick();

}