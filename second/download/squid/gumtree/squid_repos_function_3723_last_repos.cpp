void Adaptation::Icap::OptXact::finalizeLogInfo()
{
    //    al.cache.caddr = 0;
    al.icap.reqMethod = Adaptation::methodOptions;

    if (icapReply != NULL && al.icap.bytesRead > icapReply->hdr_sz)
        al.icap.bodyBytesRead = al.icap.bytesRead - icapReply->hdr_sz;

    Adaptation::Icap::Xaction::finalizeLogInfo();
}