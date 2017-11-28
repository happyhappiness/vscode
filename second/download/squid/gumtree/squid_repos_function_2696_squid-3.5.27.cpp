void
htcpSpecifier::checkedHit(StoreEntry *e)
{
    if (e) {
        htcpTstReply(dhdr, e, this, from);      /* hit */
        htcpLogHtcp(from, dhdr->opcode, LOG_UDP_HIT, uri);
    } else {
        htcpTstReply(dhdr, NULL, NULL, from);   /* cache miss */
        htcpLogHtcp(from, dhdr->opcode, LOG_UDP_MISS, uri);
    }

    htcpFreeSpecifier(this);
}