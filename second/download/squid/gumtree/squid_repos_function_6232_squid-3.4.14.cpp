bool
Eui::Eui64::encode(char *buf, const int len)
{
    if (len < SZ_EUI64_BUF) return false;

    snprintf(buf, len, "%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x",
             eui[0], eui[1], eui[2], eui[3],
             eui[4], eui[5], eui[6], eui[7]);
    debugs(28, 4, "id=" << (void*)this << " encoded " << buf);
    return true;
}