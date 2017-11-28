void
ESIContext::trimBlanks()
{
    /* trim leading empty buffers ? */

    while (outbound.getRaw() && outbound->next.getRaw() && !outbound->len) {
        debugs(86, 5, "ESIContext::trimBlanks: " << this <<
               " skipping segment " << outbound.getRaw());
        outbound = outbound->next;
    }

    if (outboundtail.getRaw())
        assert (outbound.getRaw());
}