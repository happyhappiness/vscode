void
UrnState::start(HttpRequest * r, StoreEntry * e)
{
    debugs(52, 3, "urnStart: '" << e->url() << "'" );
    entry = e;
    request = r;

    entry->lock();
    setUriResFromRequest(r);

    if (urlres_r == NULL)
        return;

    StoreEntry::getPublic (this, urlres, Http::METHOD_GET);
}