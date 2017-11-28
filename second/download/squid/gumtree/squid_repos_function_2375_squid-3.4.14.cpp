static unsigned short
idnsQueryID(void)
{
    unsigned short id = squid_random() & 0xFFFF;
    unsigned short first_id = id;

    while (idnsFindQuery(id)) {
        ++id;

        if (id == first_id) {
            debugs(78, DBG_IMPORTANT, "idnsQueryID: Warning, too many pending DNS requests");
            break;
        }
    }

    return id;
}