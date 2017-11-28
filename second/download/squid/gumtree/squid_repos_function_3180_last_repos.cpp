void
UrnState::setUriResFromRequest(HttpRequest *r)
{
    static const SBuf menu(".menu");
    if (r->url.path().startsWith(menu)) {
        r->url.path(r->url.path().substr(5)); // strip prefix "menu."
        flags.force_menu = true;
    }

    SBuf uri = r->url.path();
    LOCAL_ARRAY(char, local_urlres, 4096);
    char *host = getHost(uri);
    snprintf(local_urlres, 4096, "http://%s/uri-res/N2L?urn:" SQUIDSBUFPH, host, SQUIDSBUFPRINT(uri));
    safe_free(host);
    safe_free(urlres);
    urlres = xstrdup(local_urlres);
    urlres_r = HttpRequest::FromUrl(urlres, r->masterXaction);

    if (urlres_r == NULL) {
        debugs(52, 3, "urnStart: Bad uri-res URL " << urlres);
        ErrorState *err = new ErrorState(ERR_URN_RESOLVE, Http::scNotFound, r);
        err->url = urlres;
        urlres = NULL;
        errorAppendEntry(entry, err);
        return;
    }

    urlres_r->header.putStr(Http::HdrType::ACCEPT, "text/plain");
}