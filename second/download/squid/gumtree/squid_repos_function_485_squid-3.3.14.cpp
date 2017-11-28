static void
OutputHHA1(RequestData * requestData)
{
    requestData->error = 0;
    GetHHA1(requestData);
    if (requestData->error) {
        SEND_ERR("No such user");
        return;
    }
    printf("%s\n", requestData->HHA1);
}