static char *get_port_key(conn_rec *c)
{
    seclistenup_rec *sl;

    for (sl = ap_seclistenersup; sl; sl = sl->next) {
        if ((sl->port == (c->local_addr)->port) &&
            ((strcmp(sl->addr, "0.0.0.0") == 0) || (strcmp(sl->addr, c->local_ip) == 0))) {
            return sl->key;
        }
    }
    return NULL;
}