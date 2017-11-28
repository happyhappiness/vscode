void
HttpHeader::clean()
{

    assert(owner > hoNone && owner < hoEnd);
    debugs(55, 7, "cleaning hdr: " << this << " owner: " << owner);

    PROF_start(HttpHeaderClean);

    if (owner <= hoReply) {
        /*
         * An unfortunate bug.  The entries array is initialized
         * such that count is set to zero.  httpHeaderClean() seems to
         * be called both when 'hdr' is created, and destroyed.  Thus,
         * we accumulate a large number of zero counts for 'hdr' before
         * it is ever used.  Can't think of a good way to fix it, except
         * adding a state variable that indicates whether or not 'hdr'
         * has been used.  As a hack, just never count zero-sized header
         * arrays.
         */
        if (!entries.empty())
            HttpHeaderStats[owner].hdrUCountDistr.count(entries.size());

        ++ HttpHeaderStats[owner].destroyedCount;

        HttpHeaderStats[owner].busyDestroyedCount += entries.size() > 0;
    } // if (owner <= hoReply)

    for (std::vector<HttpHeaderEntry *>::iterator i = entries.begin(); i != entries.end(); ++i) {
        HttpHeaderEntry *e = *i;
        if (e == NULL)
            continue;
        if (e->id < 0 || e->id >= HDR_ENUM_END) {
            debugs(55, DBG_CRITICAL, "BUG: invalid entry (" << e->id << "). Ignored.");
        } else {
            if (owner <= hoReply)
                HttpHeaderStats[owner].fieldTypeDistr.count(e->id);
            delete e;
        }
    }

    entries.clear();
    httpHeaderMaskInit(&mask, 0);
    len = 0;
    conflictingContentLength_ = false;
    PROF_stop(HttpHeaderClean);
}