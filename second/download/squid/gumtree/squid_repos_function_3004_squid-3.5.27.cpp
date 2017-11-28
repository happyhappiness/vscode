static int
wccpLowestIP(void)
{
    unsigned int loop;
    int found = 0;

    /*
     * We sanity checked wccp_i_see_you.number back in wccpHandleUdp()
     */

    for (loop = 0; loop < (unsigned) ntohl(wccp_i_see_you.number); ++loop) {
        assert(loop < WCCP_ACTIVE_CACHES);

        if (local_ip > wccp_i_see_you.wccp_cache_entry[loop].ip_addr)
            return 0;

        if (local_ip == wccp_i_see_you.wccp_cache_entry[loop].ip_addr)
            found = 1;
    }

    return found;
}