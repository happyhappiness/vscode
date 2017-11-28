void
ESIContext::appendOutboundData(ESISegment::Pointer theData)
{
    if (!outbound.getRaw()) {
        outbound = theData;
        outboundtail = outbound;
    } else {
        assert (outboundtail->next.getRaw() == NULL);
        outboundtail->next = theData;
    }

    fixupOutboundTail();
    debugs(86, 9, "ESIContext::appendOutboundData: outbound " << outbound.getRaw());
}