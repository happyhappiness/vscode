nfmark_t
GetNfmarkToServer(HttpRequest * request)
{
    ACLFilledChecklist ch(NULL, request, NULL);
    return aclMapNfmark(Ip::Qos::TheConfig.nfmarkToServer, &ch);
}