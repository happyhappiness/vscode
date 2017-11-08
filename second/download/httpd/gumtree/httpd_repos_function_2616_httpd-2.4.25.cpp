static void ev_init(h2_proxy_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_PROXYS_ST_INIT:
            if (h2_proxy_ihash_empty(session->streams)) {
                transit(session, "init", H2_PROXYS_ST_IDLE);
            }
            else {
                transit(session, "init", H2_PROXYS_ST_BUSY);
            }
            break;

        default:
            /* nop */
            break;
    }
}