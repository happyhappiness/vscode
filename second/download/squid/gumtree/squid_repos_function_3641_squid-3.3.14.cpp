void
HttpHdrRange::getCanonizedSpecs (Vector<HttpHdrRangeSpec *> &copy)
{
    /* canonize each entry and destroy bad ones if any */

    for (iterator pos (begin()); pos != end(); ++pos) {
        if ((*pos)->canonize(clen))
            copy.push_back (*pos);
        else
            delete (*pos);
    }

    debugs(64, 3, "HttpHdrRange::getCanonizedSpecs: found " <<
           specs.size() - copy.size() << " bad specs");
}