
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
        ErrorState *err = new ErrorState(ERR_URN_RESOLVE, HTTP_NOT_FOUND, r);
        err->url = urlres;
        urlres = NULL;
        errorAppendEntry(entry, err);
        return;
    }

    HTTPMSGLOCK(urlres_r);
    urlres_r->header.putStr(HDR_ACCEPT, "text/plain");
}

void
UrnState::start(HttpRequest * r, StoreEntry * e)
{
    debugs(52, 3, "urnStart: '" << e->url() << "'" );
    entry = e;
    request = HTTPMSGLOCK(r);

    entry->lock();
    setUriResFromRequest(r);

    if (urlres_r == NULL)
        return;

    StoreEntry::getPublic (this, urlres, METHOD_GET);
}

void
UrnState::created(StoreEntry *newEntry)
{
    urlres_e = newEntry;

    if (urlres_e->isNull()) {
        urlres_e = storeCreateEntry(urlres, urlres, RequestFlags(), METHOD_GET);
        sc = storeClientListAdd(urlres_e, this);
        FwdState::fwdStart(Comm::ConnectionPointer(), urlres_e, urlres_r);
    } else {

        urlres_e->lock();
        sc = storeClientListAdd(urlres_e, this);
    }

    reqofs = 0;
    StoreIOBuffer tempBuffer;
