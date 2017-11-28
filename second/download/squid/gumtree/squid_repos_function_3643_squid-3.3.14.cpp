int
HttpHdrRange::canonize (int64_t newClen)
{
    clen = newClen;
    debugs(64, 3, "HttpHdrRange::canonize: started with " << specs.count <<
           " specs, clen: " << clen);
    Vector<HttpHdrRangeSpec*> goods;
    getCanonizedSpecs(goods);
    merge (goods);
    debugs(64, 3, "HttpHdrRange::canonize: finished with " << specs.count <<
           " specs");
    return specs.count > 0;
}