int ap_setup_listeners(server_rec *s)
{
    ap_listen_rec *lr;
    int num_listeners = 0;

    if (ap_listen_open(s->process->pool, s->port)) {
       return 0;
    }

    for (lr = ap_listeners; lr; lr = lr->next) {
        num_listeners++;
    }

    return num_listeners;
}