unsigned long
getOutgoingTOS(HttpRequest * request)
{
    ACLFilledChecklist ch(NULL, request, NULL);

    if (request) {
        ch.src_addr = request->client_addr;
        ch.my_addr = request->my_addr;
    }

    return aclMapTOS(Config.accessList.outgoing_tos, &ch);
}