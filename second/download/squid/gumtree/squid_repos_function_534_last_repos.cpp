bool
Transients::copyToShm(const StoreEntry &e, const sfileno index,
                      const RequestFlags &reqFlags,
                      const HttpRequestMethod &reqMethod)
{
    TransientsMapExtras::Item &extra = extras->items[index];

    const char *url = e.url();
    const size_t urlLen = strlen(url);
    Must(urlLen < sizeof(extra.url)); // we have space to store it all, plus 0
    strncpy(extra.url, url, sizeof(extra.url));
    extra.url[urlLen] = '\0';

    extra.reqFlags = reqFlags;

    Must(reqMethod != Http::METHOD_OTHER);
    extra.reqMethod = reqMethod.id();

    return true;
}