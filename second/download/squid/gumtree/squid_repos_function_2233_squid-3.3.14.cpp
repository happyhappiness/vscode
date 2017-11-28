void
MemObject::resetUrls(char const *aUrl, char const *aLog_url)
{
    safe_free(url);
    safe_free(log_url);    /* XXX account log_url */
    log_url = xstrdup(aLog_url);
    url = xstrdup(aUrl);
}