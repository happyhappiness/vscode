bool
Eui::Eui48::decode(const char *asc)
{
    int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0;

    if (sscanf(asc, "%x:%x:%x:%x:%x:%x", &a1, &a2, &a3, &a4, &a5, &a6) != 6) {
        debugs(28, DBG_CRITICAL, "Decode EUI-48: Invalid ethernet address '" << asc << "'");
        clear();
        return false;       /* This is not valid address */
    }

    eui[0] = (u_char) a1;
    eui[1] = (u_char) a2;
    eui[2] = (u_char) a3;
    eui[3] = (u_char) a4;
    eui[4] = (u_char) a5;
    eui[5] = (u_char) a6;

    debugs(28, 4, "id=" << (void*)this << " decoded " << asc);
    return true;
}