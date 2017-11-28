static void
squidaio_do_write(squidaio_request_t * requestp)
{
    if (!WriteFile((HANDLE)_get_osfhandle(requestp->fd), requestp->bufferp,
                   requestp->buflen, (LPDWORD)&requestp->ret, NULL)) {
        WIN32_maperror(GetLastError());
        requestp->ret = -1;
    }

    requestp->err = errno;
}