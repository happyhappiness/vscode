void
HttpHdrRange::getCanonizedSpecs(std::vector<HttpHdrRangeSpec *> &copy)
{
    /* canonize each entry and destroy bad ones if any */

    for (iterator pos (begin()); pos != end(); ++pos) {
        if ((*pos)->canonize(clen))
            copy.push_back (*pos);
        else
            delete (*pos);
    }

    debugs(64, 3, "found " << specs.size() - copy.size() << " bad specs");
}