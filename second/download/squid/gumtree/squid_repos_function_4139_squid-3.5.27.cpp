void Adaptation::Icap::ModXact::maybeAllocateHttpMsg()
{
    if (adapted.header) // already allocated
        return;

    if (gotEncapsulated("res-hdr")) {
        adapted.setHeader(new HttpReply);
        setOutcome(service().cfg().method == ICAP::methodReqmod ?
                   xoSatisfied : xoModified);
    } else if (gotEncapsulated("req-hdr")) {
        adapted.setHeader(new HttpRequest);
        setOutcome(xoModified);
    } else
        throw TexcHere("Neither res-hdr nor req-hdr in maybeAllocateHttpMsg()");
}