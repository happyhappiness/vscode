tos_t
GetTosToServer(HttpRequest * request)
{
    ACLFilledChecklist ch(NULL, request, NULL);
    return aclMapTOS(Ip::Qos::TheConfig.tosToServer, &ch);
}