h2_filter_cin *h2_filter_cin_create(h2_session *session)
{
    h2_filter_cin *cin;
    
    cin = apr_pcalloc(session->pool, sizeof(*cin));
    if (!cin) {
        return NULL;
    }
    cin->session = session;
    return cin;
}