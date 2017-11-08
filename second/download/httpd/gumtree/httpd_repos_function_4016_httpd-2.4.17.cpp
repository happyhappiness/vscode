static int event_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                             apr_pool_t *ptemp, server_rec *s)
{
    struct {
        struct timeout_queue *tail, *q;
        apr_hash_t *hash;
    } wc, ka;

    /* Not needed in pre_config stage */
    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG) {
        return OK;
    }

    wc.tail = ka.tail = NULL;
    wc.hash = apr_hash_make(ptemp);
    ka.hash = apr_hash_make(ptemp);

    TO_QUEUE_INIT(linger_q, pconf,
                  apr_time_from_sec(MAX_SECS_TO_LINGER), NULL);
    TO_QUEUE_INIT(short_linger_q, pconf,
                  apr_time_from_sec(SECONDS_TO_LINGER), NULL);

    for (; s; s = s->next) {
        event_srv_cfg *sc = apr_pcalloc(pconf, sizeof *sc);

        ap_set_module_config(s->module_config, &mpm_event_module, sc);
        if (!wc.tail) {
            /* The main server uses the global queues */
            TO_QUEUE_INIT(wc.q, pconf, s->timeout, NULL);
            apr_hash_set(wc.hash, &s->timeout, sizeof s->timeout, wc.q);
            wc.tail = write_completion_q = wc.q;

            TO_QUEUE_INIT(ka.q, pconf, s->keep_alive_timeout, NULL);
            apr_hash_set(ka.hash, &s->keep_alive_timeout,
                         sizeof s->keep_alive_timeout, ka.q);
            ka.tail = keepalive_q = ka.q;
        }
        else {
            /* The vhosts use any existing queue with the same timeout,
             * or their own queue(s) if there isn't */
            wc.q = apr_hash_get(wc.hash, &s->timeout, sizeof s->timeout);
            if (!wc.q) {
                TO_QUEUE_INIT(wc.q, pconf, s->timeout, wc.tail);
                apr_hash_set(wc.hash, &s->timeout, sizeof s->timeout, wc.q);
                wc.tail = wc.tail->next = wc.q;
            }

            ka.q = apr_hash_get(ka.hash, &s->keep_alive_timeout,
                                sizeof s->keep_alive_timeout);
            if (!ka.q) {
                TO_QUEUE_INIT(ka.q, pconf, s->keep_alive_timeout, ka.tail);
                apr_hash_set(ka.hash, &s->keep_alive_timeout,
                             sizeof s->keep_alive_timeout, ka.q);
                ka.tail = ka.tail->next = ka.q;
            }
        }
        sc->wc_q = wc.q;
        sc->ka_q = ka.q;
    }

    return OK;
}