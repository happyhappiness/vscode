void
Http::Stream::prepareReply(HttpReply *rep)
{
    reply = rep;
    if (http->request->range)
        buildRangeHeader(rep);
}