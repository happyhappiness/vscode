HttpReply *
HttpReply::clone() const
{
    HttpReply *rep = new HttpReply();
    rep->sline = sline; // used in hdrCacheInit() call below
    rep->header.append(&header);
    rep->hdrCacheInit();
    rep->hdr_sz = hdr_sz;
    rep->http_ver = http_ver;
    rep->pstate = pstate;
    rep->body_pipe = body_pipe;

    // keep_alive is handled in hdrCacheInit()
    return rep;
}