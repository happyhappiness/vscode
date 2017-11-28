static void
wccpHandleUdp(int sock, void *not_used)
{
    Ip::Address from;
    int len;

    debugs(80, 6, "wccpHandleUdp: Called.");

    Comm::SetSelect(sock, COMM_SELECT_READ, wccpHandleUdp, NULL, 0);

    memset(&wccp_i_see_you, '\0', sizeof(wccp_i_see_you));

    len = comm_udp_recvfrom(sock,
                            (void *) &wccp_i_see_you,
                            sizeof(wccp_i_see_you),
                            0,
                            from);
    debugs(80, 3, "wccpHandleUdp: " << len << " bytes WCCP pkt from " << from <<
           ": type=" <<
           (unsigned) ntohl(wccp_i_see_you.type) << ", version=" <<
           (unsigned) ntohl(wccp_i_see_you.version) << ", change=" <<
           (unsigned) ntohl(wccp_i_see_you.change) << ", id=" <<
           (unsigned) ntohl(wccp_i_see_you.id) << ", number=" <<
           (unsigned) ntohl(wccp_i_see_you.number));

    if (len < 0)
        return;

    if (from != Config.Wccp.router)
        return;

    if ((unsigned) ntohl(wccp_i_see_you.version) != (unsigned) Config.Wccp.version)
        return;

    if (ntohl(wccp_i_see_you.type) != WCCP_I_SEE_YOU)
        return;

    if (ntohl(wccp_i_see_you.number) > WCCP_ACTIVE_CACHES) {
        debugs(80, DBG_IMPORTANT, "Ignoring WCCP_I_SEE_YOU from " <<
               from << " with number of caches set to " <<
               (int) ntohl(wccp_i_see_you.number));

        return;
    }

    last_id = wccp_i_see_you.id;

    if ((0 == last_change) && (number_caches == (unsigned) ntohl(wccp_i_see_you.number))) {
        if (last_assign_buckets_change == wccp_i_see_you.change) {
            /*
             * After a WCCP_ASSIGN_BUCKET message, the router should
             * update the change value.  If not, maybe the route didn't
             * receive our WCCP_ASSIGN_BUCKET message, so send it again.
             *
             * Don't update change here.  Instead, fall through to
             * the next block to call wccpAssignBuckets() again.
             */
            (void) 0;
        } else {
            last_change = wccp_i_see_you.change;
            return;
        }
    }

    if (last_change != wccp_i_see_you.change) {
        last_change = wccp_i_see_you.change;

        if (wccpLowestIP() && wccp_i_see_you.number) {
            last_assign_buckets_change = last_change;
            wccpAssignBuckets();
        }
    }
}