HttpRequest *
HttpRequest::FromUrl(char * url, const MasterXaction::Pointer &mx, const HttpRequestMethod& method)
{
    std::unique_ptr<HttpRequest> req(new HttpRequest(mx));
    if (req->url.parse(method, url)) {
        req->method = method;
        return req.release();
    }
    return nullptr;
}