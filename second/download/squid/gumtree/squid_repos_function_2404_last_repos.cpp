int
HttpRequest::prefixLen() const
{
    return method.image().length() + 1 +
           url.path().length() + 1 +
           4 + 1 + 3 + 2 +
           header.len + 2;
}