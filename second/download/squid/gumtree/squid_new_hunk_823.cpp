void
HttpStateData::sentRequestBody(const CommIoCbParams &io)
{
    if (io.size > 0)
        kb_incr(&statCounter.server.http.kbytes_out, io.size);

    Client::sentRequestBody(io);
}

void
HttpStateData::abortAll(const char *reason)
{
    debugs(11,5, HERE << "aborting transaction for " << reason <<
           "; " << serverConnection << ", this " << this);
    mustStop(reason);
}

