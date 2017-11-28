static htcpDetail *
htcpUnpackDetail(char *buf, int sz)
{
    htcpDetail *d = static_cast<htcpDetail *>(htcpDetailPool->alloc());

    /* Find length of RESP-HDRS */
    uint16_t l = ntohs(*(uint16_t *) buf);
    sz -= 2;
    buf += 2;

    if (l > sz) {
        debugs(31, 3, "htcpUnpackDetail: failed to unpack RESP_HDRS");
        htcpFreeDetail(d);
        return NULL;
    }

    /* Set RESP-HDRS */
    d->resp_hdrs = buf;

    buf += l;

    sz -= l;

    /* Find length of ENTITY-HDRS */
    l = ntohs(*(uint16_t *) buf);

    sz -= 2;

    if (l > sz) {
        debugs(31, 3, "htcpUnpackDetail: failed to unpack ENTITY_HDRS");
        htcpFreeDetail(d);
        return NULL;
    }

    /* Add terminating null to RESP-HDRS */
    *buf = '\0';

    /* Set ENTITY-HDRS */
    buf += 2;

    d->entity_hdrs = buf;

    buf += l;

    sz -= l;

    /* Find length of CACHE-HDRS */
    l = ntohs(*(uint16_t *) buf);

    sz -= 2;

    if (l > sz) {
        debugs(31, 3, "htcpUnpackDetail: failed to unpack CACHE_HDRS");
        htcpFreeDetail(d);
        return NULL;
    }

    /* Add terminating null to ENTITY-HDRS */
    *buf = '\0';

    /* Set CACHE-HDRS */
    buf += 2;

    d->cache_hdrs = buf;

    buf += l;

    sz -= l;

    debugs(31, 3, "htcpUnpackDetail: " << sz << " bytes left");

    /*
     * Add terminating null to CACHE-HDRS. This is possible because we allocated
     * an extra byte when we received the packet. This will overwrite any following
     * AUTH block.
     */
    *buf = '\0';

    return d;
}