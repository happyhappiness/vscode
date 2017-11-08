static void setup_slave_conn(conn_rec *c, void *csd) 
{
    event_conn_state_t *mcs;
    event_conn_state_t *cs;
    
    mcs = ap_get_module_config(c->master->conn_config, &mpm_event_module);
    
    cs = apr_pcalloc(c->pool, sizeof(*cs));
    cs->c = c;
    cs->r = NULL;
    cs->sc = mcs->sc;
    cs->suspended = 0;
    cs->p = c->pool;
    cs->bucket_alloc = c->bucket_alloc;
    cs->pfd = mcs->pfd;
    cs->pub = mcs->pub;
    cs->pub.state = CONN_STATE_READ_REQUEST_LINE;
    cs->pub.sense = CONN_SENSE_DEFAULT;
    
    c->cs = &(cs->pub);
    ap_set_module_config(c->conn_config, &mpm_event_module, cs);
}