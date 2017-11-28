}

void
HttpStateData::httpStateConnClosed(const CommCloseCbParams &params)
{
    debugs(11, 5, "httpStateFree: FD " << params.fd << ", httpState=" << params.data);
    mustStop("HttpStateData::httpStateConnClosed");
}

void
HttpStateData::httpTimeout(const CommTimeoutCbParams &params)
{
    debugs(11, 4, HERE << serverConnection << ": '" << entry->url() << "'" );

    if (entry->store_status == STORE_PENDING) {
        fwd->fail(new ErrorState(ERR_READ_TIMEOUT, Http::scGatewayTimeout, fwd->request));
    }

    serverConnection->close();
}

static void
httpMaybeRemovePublic(StoreEntry * e, Http::StatusCode status)
{
    int remove = 0;
    int forbidden = 0;
    StoreEntry *pe;

    if (!EBIT_TEST(e->flags, KEY_PRIVATE))
        return;

    switch (status) {

    case Http::scOkay:

    case Http::scNonAuthoritativeInformation:

    case Http::scMultipleChoices:

    case Http::scMovedPermanently:

    case Http::scFound:

    case Http::scGone:

    case Http::scNotFound:
        remove = 1;

        break;
