static int ap_proxy_retry_worker(const char *proxy_function, proxy_worker *worker,
        server_rec *s)
{
    if (worker->s->status & PROXY_WORKER_IN_ERROR) {
        if (apr_time_now() > worker->s->error_time + worker->s->retry) {
            ++worker->s->retries;
            worker->s->status &= ~PROXY_WORKER_IN_ERROR;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00932)
                         "%s: worker for (%s) has been marked for retry",
                         proxy_function, worker->s->hostname);
            return OK;
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00933)
                         "%s: too soon to retry worker for (%s)",
                         proxy_function, worker->s->hostname);
            return DECLINED;
        }
    }
    else {
        return OK;
    }
}