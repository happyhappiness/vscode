static void
DoOneRequest(char *buf)
{
    RequestData requestData;
    ParseBuffer(buf, &requestData);
    if (!requestData.parsed) {
        SEND_BH("message=\"Invalid line received\"");
        return;
    }
    OutputHHA1(&requestData);
}