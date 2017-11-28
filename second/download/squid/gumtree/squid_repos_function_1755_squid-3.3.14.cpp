static int
peerDigestSetCBlock(PeerDigest * pd, const char *buf)
{
    StoreDigestCBlock cblock;
    int freed_size = 0;
    const char *host = pd->host.termedBuf();

    memcpy(&cblock, buf, sizeof(cblock));
    /* network -> host conversions */
    cblock.ver.current = ntohs(cblock.ver.current);
    cblock.ver.required = ntohs(cblock.ver.required);
    cblock.capacity = ntohl(cblock.capacity);
    cblock.count = ntohl(cblock.count);
    cblock.del_count = ntohl(cblock.del_count);
    cblock.mask_size = ntohl(cblock.mask_size);
    debugs(72, 2, "got digest cblock from " << host << "; ver: " <<
           (int) cblock.ver.current << " (req: " << (int) cblock.ver.required <<
           ")");

    debugs(72, 2, "\t size: " <<
           cblock.mask_size << " bytes, e-cnt: " <<
           cblock.count << ", e-util: " <<
           xpercentInt(cblock.count, cblock.capacity) << "%" );
    /* check version requirements (both ways) */

    if (cblock.ver.required > CacheDigestVer.current) {
        debugs(72, DBG_IMPORTANT, "" << host << " digest requires version " <<
               cblock.ver.required << "; have: " << CacheDigestVer.current);

        return 0;
    }

    if (cblock.ver.current < CacheDigestVer.required) {
        debugs(72, DBG_IMPORTANT, "" << host << " digest is version " <<
               cblock.ver.current << "; we require: " <<
               CacheDigestVer.required);

        return 0;
    }

    /* check consistency */
    if (cblock.ver.required > cblock.ver.current ||
            cblock.mask_size <= 0 || cblock.capacity <= 0 ||
            cblock.bits_per_entry <= 0 || cblock.hash_func_count <= 0) {
        debugs(72, DBG_CRITICAL, "" << host << " digest cblock is corrupted.");
        return 0;
    }

    /* check consistency further */
    if ((size_t)cblock.mask_size != cacheDigestCalcMaskSize(cblock.capacity, cblock.bits_per_entry)) {
        debugs(72, DBG_CRITICAL, host << " digest cblock is corrupted " <<
               "(mask size mismatch: " << cblock.mask_size << " ? " <<
               cacheDigestCalcMaskSize(cblock.capacity, cblock.bits_per_entry)
               << ").");
        return 0;
    }

    /* there are some things we cannot do yet */
    if (cblock.hash_func_count != CacheDigestHashFuncCount) {
        debugs(72, DBG_CRITICAL, "" << host << " digest: unsupported #hash functions: " <<
               cblock.hash_func_count << " ? " << CacheDigestHashFuncCount << ".");
        return 0;
    }

    /*
     * no cblock bugs below this point
     */
    /* check size changes */
    if (pd->cd && cblock.mask_size != (ssize_t)pd->cd->mask_size) {
        debugs(72, 2, host << " digest changed size: " << cblock.mask_size <<
               " -> " << pd->cd->mask_size);
        freed_size = pd->cd->mask_size;
        cacheDigestDestroy(pd->cd);
        pd->cd = NULL;
    }

    if (!pd->cd) {
        debugs(72, 2, "creating " << host << " digest; size: " << cblock.mask_size << " (" <<
               std::showpos <<  (int) (cblock.mask_size - freed_size) << ") bytes");
        pd->cd = cacheDigestCreate(cblock.capacity, cblock.bits_per_entry);

        if (cblock.mask_size >= freed_size)
            kb_incr(&statCounter.cd.memory, cblock.mask_size - freed_size);
    }

    assert(pd->cd);
    /* these assignments leave us in an inconsistent state until we finish reading the digest */
    pd->cd->count = cblock.count;
    pd->cd->del_count = cblock.del_count;
    return 1;
}