static void Q_DBG(char*msg, apr_queue_t *q) {
    fprintf(stderr, "%ld\t#%d in %d out %d\t%s\n", 
                    apr_os_thread_current(),
                    q->nelts, q->in, q->out,
                    msg
                    );
}