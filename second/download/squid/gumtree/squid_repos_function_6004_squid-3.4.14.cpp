void
ESIContext::fixupOutboundTail()
{
    /* TODO: fixup thisNode outboundtail dross a little */

    if (outboundtail.getRaw())
        outboundtail = outboundtail->tail();
}