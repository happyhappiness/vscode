int aio_error(const struct aiocb * aiocbp)
{
    return aiocbp->aio_sigevent.sigev_notify;
}