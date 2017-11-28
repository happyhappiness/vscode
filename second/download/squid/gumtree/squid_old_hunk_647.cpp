
static void
OutputHHA1(RequestData * requestData)
{
    requestData->error = 0;
    GetHHA1(requestData);
    if (requestData->error) {
        SEND_ERR("message=\"No such user\"");
        return;
    }
    printf("OK ha1=\"%s\"\n", requestData->HHA1);
}
