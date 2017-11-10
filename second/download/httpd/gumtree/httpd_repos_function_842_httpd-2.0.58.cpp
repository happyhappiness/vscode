static int ssl_rand_feedfp(apr_pool_t *p, apr_file_t *fp, int nReq)
{
    apr_size_t nDone;
    unsigned char caBuf[BUFSIZE];
    apr_size_t nBuf;
    apr_size_t nRead;
    apr_size_t nTodo;

    nDone = 0;
    nRead = BUFSIZE;
    nTodo = nReq;
    while (1) {
        if (nReq > 0)
            nRead = (nTodo < BUFSIZE ? nTodo : BUFSIZE);
        nBuf = nRead;
        if (apr_file_read(fp, caBuf, &nBuf) != APR_SUCCESS)
            break;
        RAND_seed(caBuf, nBuf);
        nDone += nBuf;
        if (nReq > 0) {
            nTodo -= nBuf;
            if (nTodo <= 0)
                break;
        }
    }
    return nDone;
}