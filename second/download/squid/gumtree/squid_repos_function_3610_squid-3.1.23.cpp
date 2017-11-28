void
UrnState::setUriResFromRequest(HttpRequest *r)
{
    if (RequestNeedsMenu(r)) {
        updateRequestURL(r, r->urlpath.rawBuf() + 5, r->urlpath.size() - 5 );
        flags.force_menu = 1;
    }

    createUriResRequest (r->urlpath);

    if (urlres_r == NULL) {
        debugs(52, 3, "urnStart: Bad uri-res URL " << urlres);
        ErrorState *err = errorCon(ERR_URN_RESOLVE, HTTP_NOT_FOUND, r);
        err->url = urlres;
        urlres = NULL;
        errorAppendEntry(entry, err);
        return;
    }

    HTTPMSGLOCK(urlres_r);
    urlres_r->header.putStr(HDR_ACCEPT, "text/plain");
}