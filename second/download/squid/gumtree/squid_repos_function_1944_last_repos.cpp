static unsigned short
idnsQueryID()
{
    // NP: apparently ranlux are faster, but not quite as "proven"
    static std::mt19937 mt(static_cast<uint32_t>(getCurrentTime() & 0xFFFFFFFF));
    unsigned short id = mt() & 0xFFFF;
    unsigned short first_id = id;

    // ensure temporal uniqueness by looking for an existing use
    while (idnsFindQuery(id)) {
        ++id;

        if (id == first_id) {
            debugs(78, DBG_IMPORTANT, "idnsQueryID: Warning, too many pending DNS requests");
            break;
        }
    }

    return id;
}