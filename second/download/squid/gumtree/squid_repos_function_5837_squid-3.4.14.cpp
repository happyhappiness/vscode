ssize_t aio_return(struct aiocb * aiocbp)
{
    return aiocbp->aio_sigevent.sigev_signo;
}