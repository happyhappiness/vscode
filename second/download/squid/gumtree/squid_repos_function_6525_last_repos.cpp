int aio_error64(const struct aiocb64 * aiocbp)
{
    return aiocbp->aio_sigevent.sigev_notify;
}