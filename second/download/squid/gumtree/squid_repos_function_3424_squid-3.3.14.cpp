ErrorState *
clientBuildError(err_type page_id, http_status status, char const *url,
                 Ip::Address &src_addr, HttpRequest * request)
{
    ErrorState *err = new ErrorState(page_id, status, request);
    err->src_addr = src_addr;

    if (url)
        err->url = xstrdup(url);

    return err;
}