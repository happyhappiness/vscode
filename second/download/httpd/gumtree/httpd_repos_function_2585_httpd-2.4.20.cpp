static int has_suspended_streams(h2_session *session)
{
    int has_suspended = 0;
    h2_ihash_iter(session->streams, suspended_iter, &has_suspended);
    return has_suspended;
}