HttpRequest *
HttpRequest::CreateFromUrl(char * url)
{
    return urlParse(METHOD_GET, url, NULL);
}