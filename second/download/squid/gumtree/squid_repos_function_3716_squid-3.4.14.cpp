void
UrnState::createUriResRequest (String &uri)
{
    LOCAL_ARRAY(char, local_urlres, 4096);
    char *host = getHost (uri);
    snprintf(local_urlres, 4096, "http://%s/uri-res/N2L?urn:" SQUIDSTRINGPH,
             host, SQUIDSTRINGPRINT(uri));
    safe_free (host);
    safe_free (urlres);
    urlres = xstrdup (local_urlres);
    urlres_r = HttpRequest::CreateFromUrl(urlres);
}