static void
squidaio_do_read(squidaio_request_t * requestp)
{
    lseek(requestp->fd, requestp->offset, requestp->whence);

    if (!ReadFile((HANDLE)_get_osfhandle(requestp->fd), requestp->bufferp,
                  requestp->buflen, (LPDWORD)&requestp->ret, NULL)) {
        WIN32_maperror(GetLastError());
        requestp->ret = -1;
    }

    requestp->err = errno;
}