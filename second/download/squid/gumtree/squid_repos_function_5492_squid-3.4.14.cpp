void
headersLog(int cs, int pq, const HttpRequestMethod& method, void *data)
{
    HttpReply *rep;
    HttpRequest *req;
    unsigned short magic = 0;
    unsigned char M = (unsigned char) m;
    char *hmask;
    int ccmask = 0;

    if (0 == pq) {
        /* reply */
        rep = data;
        req = NULL;
        magic = 0x0050;
        hmask = rep->header.mask;

        if (rep->cache_control)
            ccmask = rep->cache_control->mask;
    } else {
        /* request */
        req = data;
        rep = NULL;
        magic = 0x0051;
        hmask = req->header.mask;

        if (req->cache_control)
            ccmask = req->cache_control->mask;
    }

    if (0 == cs) {
        /* client */
        magic |= 0x4300;
    } else {
        /* server */
        magic |= 0x5300;
    }

    magic = htons(magic);
    ccmask = htonl(ccmask);

    unsigned short S = 0;
    if (0 == pq)
        S = static_cast<unsigned short>(rep->sline.status());

    logfileWrite(headerslog, &magic, sizeof(magic));
    logfileWrite(headerslog, &M, sizeof(M));
    logfileWrite(headerslog, &S, sizeof(S));
    logfileWrite(headerslog, hmask, sizeof(HttpHeaderMask));
    logfileWrite(headerslog, &ccmask, sizeof(int));
}