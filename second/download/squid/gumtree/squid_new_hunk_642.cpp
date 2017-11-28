static void
DoOneRequest(char *buf)
{
    RequestData requestData;
    ParseBuffer(buf, &requestData);
    if (!requestData.parsed) {
        if (requestData.channelId >= 0)
            printf("%u ", requestData.channelId);
        SEND_BH("message=\"Invalid line received\"");
        return;
    }
    OutputHHA1(&requestData);
}

