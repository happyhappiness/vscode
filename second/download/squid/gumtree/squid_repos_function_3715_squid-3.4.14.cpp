void
UrnState::updateRequestURL(HttpRequest *r, char const *newPath, const size_t newPath_len)
{
    char *new_path = xstrndup (newPath, newPath_len);
    r->urlpath = new_path;
    xfree(new_path);
}