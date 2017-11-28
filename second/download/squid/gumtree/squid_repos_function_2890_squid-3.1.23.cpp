const char *HttpRequest::packableURI(bool full_uri) const
{
    if (full_uri)
        return urlCanonical((HttpRequest*)this);

    if (urlpath.size())
        return urlpath.termedBuf();

    return "/";
}