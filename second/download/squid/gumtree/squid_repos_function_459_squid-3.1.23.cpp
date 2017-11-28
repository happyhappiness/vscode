static void
ParseBuffer(char *buf, RequestData * requestData)
{
    char *p;
    requestData->parsed = 0;
    if ((p = strchr(buf, '\n')) != NULL)
        *p = '\0';		/* strip \n */
    if ((requestData->user = strtok(buf, "\"")) == NULL)
        return;
    if ((requestData->realm = strtok(NULL, "\"")) == NULL)
        return;
    if ((requestData->realm = strtok(NULL, "\"")) == NULL)
        return;
    requestData->parsed = -1;
}