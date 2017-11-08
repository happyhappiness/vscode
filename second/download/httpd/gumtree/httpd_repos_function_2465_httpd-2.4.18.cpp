h2_session *h2_session_create(conn_rec *c, const h2_config *config, 
                              h2_workers *workers)
{
    return h2_session_create_int(c, NULL, config, workers);
}