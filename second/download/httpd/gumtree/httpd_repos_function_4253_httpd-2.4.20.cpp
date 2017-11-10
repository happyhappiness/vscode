static int event_pre_connection(conn_rec *c, void *csd)
{
    if (c->master && (!c->cs || c->cs == c->master->cs)) {
        setup_slave_conn(c, csd);
    }
    return OK;
}