static int exipc_handler(request_rec *r)
{
    int gotlock = 0;
    int camped;
    apr_time_t startcamp;
    apr_int64_t timecamped;
    apr_status_t rs; 
    exipc_data *base;
    
    if (strcmp(r->handler, "example_ipc")) {
        return DECLINED;
    }
    
    /* 
     * The main function of the handler, aside from sending the 
     * status page to the client, is to increment the counter in 
     * the shared memory segment. This action needs to be mutexed 
     * out using the global mutex. 
     */
     
    /* 
     * First, acquire the lock. This code is a lot more involved than
     * it usually needs to be, because the process based trylock
     * routine is not implemented on unix platforms. I left it in to
     * show how it would work if trylock worked, and for situations
     * and platforms where trylock works.
     */
    for (camped = 0, timecamped = 0; camped < MAXCAMP; camped++) {
        rs = apr_global_mutex_trylock(exipc_mutex); 
        if (APR_STATUS_IS_EBUSY(rs)) {
            apr_sleep(CAMPOUT);
        } else if (APR_SUCCESS == rs) {
            gotlock = 1; 
            break; /* Get out of the loop */
        } else if (APR_STATUS_IS_ENOTIMPL(rs)) {
            /* If it's not implemented, just hang in the mutex. */
            startcamp = apr_time_now();
            rs = apr_global_mutex_lock(exipc_mutex);
            timecamped = (apr_int64_t) (apr_time_now() - startcamp);
            if (APR_SUCCESS == rs) {
                gotlock = 1;
                break; /* Out of the loop */
            } else {
                /* Some error, log and bail */
                ap_log_error(APLOG_MARK, APLOG_ERR, rs, r->server, 
                             "Child %ld failed to acquire lock", 
                             (long int)getpid());
                break; /* Out of the loop without having the lock */
            }                
        } else {
            /* Some other error, log and bail */
            ap_log_error(APLOG_MARK, APLOG_ERR, rs, r->server, 
                         "Child %ld failed to try and acquire lock", 
                         (long int)getpid());
            break; /* Out of the loop without having the lock */
            
        }
        /* 
         * The only way to get to this point is if the trylock worked
         * and returned BUSY. So, bump the time and try again
         */
        timecamped += CAMPOUT;
        ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_NOTICE, 
                     0, r->server, "Child %ld camping out on mutex for %" APR_INT64_T_FMT
                     " microseconds",
                     (long int) getpid(), timecamped);
    } /* Lock acquisition loop */
    
    /* Sleep for a millisecond to make it a little harder for
     * httpd children to acquire the lock. 
     */
    apr_sleep(SLEEPYTIME);
    
    r->content_type = "text/html";      

    if (!r->header_only) {
        ap_rputs(HTML_HEADER, r);
        if (gotlock) {
            /* Increment the counter */
            base = (exipc_data *)apr_shm_baseaddr_get(exipc_shm);
            base->counter++;
            /* Send a page with our pid and the new value of the counter. */
            ap_rprintf(r, "<p>Lock acquired after %ld microseoncds.</p>\n", 
                       (long int) timecamped); 
            ap_rputs("<table border=\"1\">\n", r);
            ap_rprintf(r, "<tr><td>Child pid:</td><td>%d</td></tr>\n", 
                       (int) getpid());
            ap_rprintf(r, "<tr><td>Counter:</td><td>%u</td></tr>\n", 
                       (unsigned int)base->counter);
            ap_rputs("</table>\n", r);
        } else {
            /* 
             * Send a page saying that we couldn't get the lock. Don't say
             * what the counter is, because without the lock the value could
             * race. 
             */
            ap_rprintf(r, "<p>Child %d failed to acquire lock "
                       "after camping out for %d microseconds.</p>\n", 
                       (int) getpid(), (int) timecamped);
        }
        ap_rputs(HTML_FOOTER, r); 
    } /* r->header_only */
    
    /* Release the lock */
    if (gotlock)
        rs = apr_global_mutex_unlock(exipc_mutex); 
    /* Swallowing the result because what are we going to do with it at 
     * this stage? 
     */

    return OK;
}