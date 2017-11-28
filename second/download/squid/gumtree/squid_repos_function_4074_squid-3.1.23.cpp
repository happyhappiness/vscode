void Adaptation::Icap::OptXact::finalizeLogInfo()
{
    //    al.cache.caddr = 0;
    al.icap.reqMethod = Adaptation::methodOptions;
    Adaptation::Icap::Xaction::finalizeLogInfo();
}