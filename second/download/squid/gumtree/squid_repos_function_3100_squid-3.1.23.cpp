ErrorState *
errorCon(err_type type, http_status status, HttpRequest * request)
{
    ErrorState *err = new ErrorState;
    err->page_id = type;	/* has to be reset manually if needed */
    err->err_language = NULL;
    err->type = type;
    err->httpStatus = status;

    if (request != NULL) {
        err->request = HTTPMSGLOCK(request);
        err->src_addr = request->client_addr;
    }

    return err;
}