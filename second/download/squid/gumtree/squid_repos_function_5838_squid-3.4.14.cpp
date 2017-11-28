ssize_t aio_return64(struct aiocb64 * aiocbp)

{
    return aiocbp->aio_sigevent.sigev_signo;
}