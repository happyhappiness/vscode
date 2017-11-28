std::ostream &operator <<(std::ostream &os, const StoreEntry &e)
{
    os << "e:";

    if (e.mem_obj) {
        if (e.mem_obj->xitTable.index > -1)
            os << 't' << e.mem_obj->xitTable.index;
        if (e.mem_obj->memCache.index > -1)
            os << 'm' << e.mem_obj->memCache.index;
    }
    if (e.swap_filen > -1 || e.swap_dirn > -1)
        os << 'd' << e.swap_filen << '@' << e.swap_dirn;

    os << '=';

    // print only non-default status values, using unique letters
    if (e.mem_status != NOT_IN_MEMORY ||
            e.store_status != STORE_PENDING ||
            e.swap_status != SWAPOUT_NONE ||
            e.ping_status != PING_NONE) {
        if (e.mem_status != NOT_IN_MEMORY) os << 'm';
        if (e.store_status != STORE_PENDING) os << 's';
        if (e.swap_status != SWAPOUT_NONE) os << 'w' << e.swap_status;
        if (e.ping_status != PING_NONE) os << 'p' << e.ping_status;
    }

    // print only set flags, using unique letters
    if (e.flags) {
        if (EBIT_TEST(e.flags, ENTRY_SPECIAL)) os << 'S';
        if (EBIT_TEST(e.flags, ENTRY_REVALIDATE_ALWAYS)) os << 'R';
        if (EBIT_TEST(e.flags, DELAY_SENDING)) os << 'P';
        if (EBIT_TEST(e.flags, RELEASE_REQUEST)) os << 'X';
        if (EBIT_TEST(e.flags, REFRESH_REQUEST)) os << 'F';
        if (EBIT_TEST(e.flags, ENTRY_REVALIDATE_STALE)) os << 'E';
        if (EBIT_TEST(e.flags, ENTRY_DISPATCHED)) os << 'D';
        if (EBIT_TEST(e.flags, KEY_PRIVATE)) {
            os << 'I';
            if (e.shareableWhenPrivate)
                os << 'H';
        }
        if (EBIT_TEST(e.flags, ENTRY_FWD_HDR_WAIT)) os << 'W';
        if (EBIT_TEST(e.flags, ENTRY_NEGCACHED)) os << 'N';
        if (EBIT_TEST(e.flags, ENTRY_VALIDATED)) os << 'V';
        if (EBIT_TEST(e.flags, ENTRY_BAD_LENGTH)) os << 'L';
        if (EBIT_TEST(e.flags, ENTRY_ABORTED)) os << 'A';
    }

    if (e.mem_obj && e.mem_obj->smpCollapsed)
        os << 'O';

    return os << '/' << &e << '*' << e.locks();
}