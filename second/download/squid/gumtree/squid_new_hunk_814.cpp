}

void
HttpStateData::httpStateConnClosed(const CommCloseCbParams &params)
{
    debugs(11, 5, "httpStateFree: FD " << params.fd << ", httpState=" << params.data);
    doneWithFwd = "httpStateConnClosed()"; // assume FwdState is monitoring too
    mustStop("HttpStateData::httpStateConnClosed");
}

void
HttpStateData::httpTimeout(const CommTimeoutCbParams &params)
{
    debugs(11, 4, HERE << serverConnection << ": '" << entry->url() << "'" );

    if (entry->store_status == STORE_PENDING) {
        fwd->fail(new ErrorState(ERR_READ_TIMEOUT, Http::scGatewayTimeout, fwd->request));
    }

    closeServer();
    mustStop("HttpStateData::httpTimeout");
}

static StoreEntry *
findPreviouslyCachedEntry(StoreEntry *newEntry) {
    assert(newEntry->mem_obj);
    return newEntry->mem_obj->request ?
           storeGetPublicByRequest(newEntry->mem_obj->request) :
           storeGetPublic(newEntry->mem_obj->storeId(), newEntry->mem_obj->method);
}

/// Remove an existing public store entry if the incoming response (to be
/// stored in a currently private entry) is going to invalidate it.
static void
httpMaybeRemovePublic(StoreEntry * e, Http::StatusCode status)
{
    int remove = 0;
    int forbidden = 0;

    // If the incoming response already goes into a public entry, then there is
    // nothing to remove. This protects ready-for-collapsing entries as well.
    if (!EBIT_TEST(e->flags, KEY_PRIVATE))
        return;

    // If the new/incoming response cannot be stored, then it does not
    // compete with the old stored response for the public key, and the
    // old stored response should be left as is.
    if (e->mem_obj->request && !e->mem_obj->request->flags.cachable)
        return;

    switch (status) {

    case Http::scOkay:

    case Http::scNonAuthoritativeInformation:

    case Http::scMultipleChoices:

    case Http::scMovedPermanently:

    case Http::scFound:

    case Http::scSeeOther:

    case Http::scGone:

    case Http::scNotFound:
        remove = 1;

        break;
