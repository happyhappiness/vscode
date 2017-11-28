void
HttpHeader::clean()
{
    HttpHeaderPos pos = HttpHeaderInitPos;
    HttpHeaderEntry *e;

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
        if (0 != entries.count)
            HttpHeaderStats[owner].hdrUCountDistr.count(entries.count);

        ++ HttpHeaderStats[owner].destroyedCount;

        HttpHeaderStats[owner].busyDestroyedCount += entries.count > 0;
    } // if (owner <= hoReply)

    while ((e = getEntry(&pos))) {
        /* tmp hack to try to avoid coredumps */

        if (e->id < 0 || e->id >= HDR_ENUM_END) {
            debugs(55, DBG_CRITICAL, "HttpHeader::clean BUG: entry[" << pos << "] is invalid (" << e->id << "). Ignored.");
        } else {
            if (owner <= hoReply)
                HttpHeaderStats[owner].fieldTypeDistr.count(e->id);
            /* yes, this deletion leaves us in an inconsistent state */
            delete e;
        }
    }
    entries.clean();
    httpHeaderMaskInit(&mask, 0);
    len = 0;
    PROF_stop(HttpHeaderClean);
}