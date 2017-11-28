static void
peerDigestFetchSetStats(DigestFetchState * fetch)
{
    MemObject *mem;
    assert(fetch->entry && fetch->request);

    mem = fetch->entry->mem_obj;
    assert(mem);

    /* XXX: outgoing numbers are not precise */
    /* XXX: we must distinguish between 304 hits and misses here */
    fetch->sent.bytes = fetch->request->prefixLen();
    /* XXX: this is slightly wrong: we don't KNOW that the entire memobject
     * was fetched. We only know how big it is
     */
    fetch->recv.bytes = mem->size();
    fetch->sent.msg = fetch->recv.msg = 1;
    fetch->expires = fetch->entry->expires;
    fetch->resp_time = squid_curtime - fetch->start_time;

    debugs(72, 3, "peerDigestFetchFinish: recv " << fetch->recv.bytes <<
           " bytes in " << (int) fetch->resp_time << " secs");

    debugs(72, 3, "peerDigestFetchFinish: expires: " <<
           (long int) fetch->expires << " (" << std::showpos <<
           (int) (fetch->expires - squid_curtime) << "), lmt: " <<
           std::noshowpos << (long int) fetch->entry->lastmod << " (" <<
           std::showpos << (int) (fetch->entry->lastmod - squid_curtime) <<
           ")");

}