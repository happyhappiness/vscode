static int has_unsubmitted_streams(h2_session *session)
{
    int has_unsubmitted = 0;
    h2_ihash_iter(session->streams, unsubmitted_iter, &has_unsubmitted);
    return has_unsubmitted;
}