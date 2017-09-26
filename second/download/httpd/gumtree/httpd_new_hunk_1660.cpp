        /* The worker share is already initialized */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
              "proxy: worker %s already initialized",
              worker->name);
        return;
    }
    if (worker->route) {
        strcpy(worker->s->route, worker->route);
    }
    else {
        *worker->s->route = '\0';
    }
    if (worker->redirect) {
        strcpy(worker->s->redirect, worker->redirect);
    }
    else {
        *worker->s->redirect = '\0';
    }

    worker->s->status |= (worker->status | PROXY_WORKER_INITIALIZED);

}

PROXY_DECLARE(apr_status_t) ap_proxy_initialize_worker(proxy_worker *worker, server_rec *s)
