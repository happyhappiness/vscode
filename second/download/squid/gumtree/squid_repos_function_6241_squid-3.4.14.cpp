bool
Eui::Eui48::encode(char *buf, const int len)
{
    if (len < SZ_EUI48_BUF)
        return false;

    snprintf(buf, len, "%02x:%02x:%02x:%02x:%02x:%02x",
             eui[0] & 0xff, eui[1] & 0xff,
             eui[2] & 0xff, eui[3] & 0xff,
             eui[4] & 0xff, eui[5] & 0xff);

    debugs(28, 4, "id=" << (void*)this << " encoded " << buf);
    return true;
}