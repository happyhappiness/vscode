int
HttpRequest::prefixLen()
{
    return method.image().length() + 1 +
           urlpath.size() + 1 +
           4 + 1 + 3 + 2 +
           header.len + 2;
}