HttpRequest *
HttpRequest::CreateFromUrlAndMethod(char * url, const HttpRequestMethod& method)
{
    return urlParse(method, url, NULL);
}