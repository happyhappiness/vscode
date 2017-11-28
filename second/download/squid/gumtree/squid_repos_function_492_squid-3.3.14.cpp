static void
DoOneRequest(char *buf)
{
    RequestData requestData;
    ParseBuffer(buf, &requestData);
    if (!requestData.parsed) {
        SEND_ERR("");
        return;
    }
    OutputHHA1(&requestData);
}