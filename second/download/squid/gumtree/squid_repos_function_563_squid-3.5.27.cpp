void
TextHHA1(RequestData * requestData)
{
    const user_data *u = GetPassword(requestData);
    if (!u) {
        requestData->error = -1;
        return;
    }
    if (u->ha1) {
        xstrncpy(requestData->HHA1, u->ha1, sizeof(requestData->HHA1));
    } else {
        HASH HA1;
        DigestCalcHA1("md5", requestData->user, requestData->realm, u->passwd, NULL, NULL, HA1, requestData->HHA1);
    }
}