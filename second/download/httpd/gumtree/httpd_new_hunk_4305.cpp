}

static int ap_proxy_retry_worker(const char *proxy_function, proxy_worker *worker,
        server_rec *s)
{
    if (worker->s->status & PROXY_WORKER_IN_ERROR) {
        if (PROXY_WORKER_IS(worker, PROXY_WORKER_STOPPED)) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(3305)
                         "%s: Won't retry worker (%s): stopped",
                         proxy_function, worker->s->hostname);
            return DECLINED;
        }
        if ((worker->s->status & PROXY_WORKER_IGNORE_ERRORS)
            || apr_time_now() > worker->s->error_time + worker->s->retry) {
            ++worker->s->retries;
            worker->s->status &= ~PROXY_WORKER_IN_ERROR;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00932)
                         "%s: worker for (%s) has been marked for retry",
                         proxy_function, worker->s->hostname);
            return OK;
