void
HttpStateData::httpTimeout(const CommTimeoutCbParams &params)
{
    debugs(11, 4, HERE << serverConnection << ": '" << entry->url() << "'" );

    if (entry->store_status == STORE_PENDING) {
        fwd->fail(new ErrorState(ERR_READ_TIMEOUT, Http::scGatewayTimeout, fwd->request));
    }

    serverConnection->close();
}