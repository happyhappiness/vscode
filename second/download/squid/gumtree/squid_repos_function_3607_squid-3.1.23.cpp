bool
UrnState::RequestNeedsMenu(HttpRequest *r)
{
    if (r->urlpath.size() < 5)
        return false;
    //now we're sure it's long enough
    return strncasecmp(r->urlpath.rawBuf(), "menu.", 5) == 0;
}