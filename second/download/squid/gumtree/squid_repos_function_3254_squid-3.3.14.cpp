static HttpRequest *
urnParse(const HttpRequestMethod& method, char *urn, HttpRequest *request)
{
    debugs(50, 5, "urnParse: " << urn);
    if (request) {
        request->initHTTP(method, AnyP::PROTO_URN, urn + 4);
        safe_free(request->canonical);
        return request;
    }

    return new HttpRequest(method, AnyP::PROTO_URN, urn + 4);
}