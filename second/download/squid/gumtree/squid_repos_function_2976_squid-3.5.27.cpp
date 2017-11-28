HttpRequest *
HttpRequest::CreateFromUrl(char * url)
{
    return urlParse(Http::METHOD_GET, url, NULL);
}