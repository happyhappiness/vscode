int
squidaio_cancel(squidaio_result_t * resultp)
{
    squidaio_request_t *request = (squidaio_request_t *)resultp->_data;

    if (request && request->resultp == resultp) {
        debugs(43, 9, "squidaio_cancel: " << request << " type=" << request->request_type << " result=" << request->resultp);
        request->cancelled = 1;
        request->resultp = NULL;
        resultp->_data = NULL;
        resultp->result_type = _AIO_OP_NONE;
        return 0;
    }

    return 1;
}