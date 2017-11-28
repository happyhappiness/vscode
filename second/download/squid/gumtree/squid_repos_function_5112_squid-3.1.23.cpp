int
squidaio_opendir(const char *path, squidaio_result_t * resultp)
{
    squidaio_request_t *requestp;
    int len;

    requestp = squidaio_request_pool->alloc();

    resultp->result_type = _AIO_OP_OPENDIR;

    return -1;
}