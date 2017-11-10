h2_session *h2_session_rcreate(request_rec *r, const h2_config *config, 
                               h2_workers *workers)
{
    return h2_session_create_int(r->connection, r, config, workers);
}