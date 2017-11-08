static void bucket_destroy(void *data)
{
    h2_bucket_eoc *h = data;

    if (apr_bucket_shared_destroy(h)) {
        h2_session *session = h->session;
        apr_bucket_free(h);
        if (session) {
            h2_session_eoc_callback(session);
            /* all is gone now */
        }
    }
}