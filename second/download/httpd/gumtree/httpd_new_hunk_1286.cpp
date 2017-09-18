{
    unsigned char tempasn[SSL_SESSION_MAX_DER];
    SHMCBIndex *idx;
    SHMCBHeader *header;
    SSL_SESSION *pSession = NULL;
    unsigned int curr_pos, loop, count;
    MODSSL_D2I_SSL_SESSION_CONST unsigned char *ptr;
    time_t now;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "entering shmcb_lookup_session_id");

    /* If there are entries to expire, ditch them first thing. */
