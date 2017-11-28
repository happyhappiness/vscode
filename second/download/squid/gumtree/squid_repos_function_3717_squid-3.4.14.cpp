void
UrnState::setUriResFromRequest(HttpRequest *r)
{
    if (RequestNeedsMenu(r)) {
        updateRequestURL(r, r->urlpath.rawBuf() + 5, r->urlpath.size() - 5 );
        flags.force_menu = true;
    }

    createUriResRequest (r->urlpath);

    if (urlres_r == NULL) {
        debugs(52, 3, "urnStart: Bad uri-res URL " << urlres);
        ErrorState *err = new ErrorState(ERR_URN_RESOLVE, Http::scNotFound, r);
        err->url = urlres;
        urlres = NULL;
        errorAppendEntry(entry, err);
        return;
    }

    urlres_r->header.putStr(HDR_ACCEPT, "text/plain");
}