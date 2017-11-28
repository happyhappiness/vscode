int
Ip::Qos::getNfMarkCallback(enum nf_conntrack_msg_type type,
                           struct nf_conntrack *ct,
                           void *data)
{
    fde *clientFde = (fde *)data;
    clientFde->nfmarkFromServer = nfct_get_attr_u32(ct, ATTR_MARK);
    debugs(17, 3, "QOS: Retrieved connection mark value: " << clientFde->nfmarkFromServer);

    return NFCT_CB_CONTINUE;
}