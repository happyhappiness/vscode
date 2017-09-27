            break;
    }
    apr_atomic_dec32(&connection_count);
    return APR_SUCCESS;
}

static void notify_suspend(event_conn_state_t *cs)
{
    ap_run_suspend_connection(cs->c, cs->r);
    cs->suspended = 1;
    cs->c->sbh = NULL;
}
