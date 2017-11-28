static void
DoOneRequest(char *buf)
{
    RequestData requestData;
    ParseBuffer(buf, &requestData);
    if (!requestData.parsed) {
        printf("ERR\n");
        return;
    }
    OutputHHA1(&requestData);
}