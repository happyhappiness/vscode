int
HttpRequest::prefixLen()
{
    return strlen(RequestMethodStr(method)) + 1 +
           urlpath.size() + 1 +
           4 + 1 + 3 + 2 +
           header.len + 2;
}