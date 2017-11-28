int
HttpHdrRange::canonize (int64_t newClen)
{
    clen = newClen;
    debugs(64, 3, "HttpHdrRange::canonize: started with " << specs.size() <<
           " specs, clen: " << clen);
    std::vector<HttpHdrRangeSpec*> goods;
    getCanonizedSpecs(goods);
    merge (goods);
    debugs(64, 3, "HttpHdrRange::canonize: finished with " << specs.size() <<
           " specs");
    return specs.size() > 0; // fixme, should return bool
}