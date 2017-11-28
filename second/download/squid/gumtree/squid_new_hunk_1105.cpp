
// called when we wrote request headers(!) or a part of the body
void
HttpStateData::sentRequestBody(const CommIoCbParams &io)
{
    if (io.size > 0)
        statCounter.server.http.kbytes_out += io.size;

    Client::sentRequestBody(io);
}

void
HttpStateData::abortAll(const char *reason)
{
    debugs(11,5, HERE << "aborting transaction for " << reason <<
           "; " << serverConnection << ", this " << this);
    mustStop(reason);
}

