void Adaptation::Icap::Xaction::finalizeLogInfo()
{
    //prepare log data
    al.icp.opcode = ICP_INVALID;

    const Adaptation::Icap::ServiceRep &s = service();
    al.icap.hostAddr = s.cfg().host.termedBuf();
    al.icap.serviceName = s.cfg().key;
    al.icap.reqUri = s.cfg().uri;

    al.icap.ioTime = tvSubMsec(icap_tio_start, icap_tio_finish);
    al.icap.trTime = tvSubMsec(icap_tr_start, current_time);

    al.icap.request = icapRequest;
    HTTPMSGLOCK(al.icap.request);
    if (icapReply != NULL) {
        al.icap.reply = icapReply.getRaw();
        HTTPMSGLOCK(al.icap.reply);
        al.icap.resStatus = icapReply->sline.status();
    }
}