void
HttpStateData::httpTimeout(const CommTimeoutCbParams &params)
{
    debugs(11, 4, "httpTimeout: FD " << fd << ": '" << entry->url() << "'" );

    if (entry->store_status == STORE_PENDING) {
        fwd->fail(errorCon(ERR_READ_TIMEOUT, HTTP_GATEWAY_TIMEOUT, fwd->request));
    }

    comm_close(fd);
}