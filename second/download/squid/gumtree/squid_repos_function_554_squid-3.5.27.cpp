static void
ParseBuffer(char *buf, RequestData * requestData)
{
    char *p;
    requestData->parsed = 0;
    if ((p = strchr(buf, '\n')) != NULL)
        *p = '\0';      /* strip \n */

    p = NULL;
    requestData->channelId = strtoll(buf, &p, 10);
    if (*p != ' ') // not a channel-ID
        requestData->channelId = -1;
    else
        buf = ++p;

    if ((requestData->user = strtok(buf, "\"")) == NULL)
        return;
    if ((requestData->realm = strtok(NULL, "\"")) == NULL)
        return;
    if ((requestData->realm = strtok(NULL, "\"")) == NULL)
        return;
    requestData->parsed = -1;
}