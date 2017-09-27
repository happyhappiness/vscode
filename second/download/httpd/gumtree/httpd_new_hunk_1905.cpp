#include "apr_allocator.h"

#include "httpd.h"
#include "http_config.h"
#include "http_log.h"
#include "http_main.h"
#include "mpm_common.h"
#include "ap_mpm.h"
#include "ap_listen.h"
#include "util_mutex.h"

#include "scoreboard.h"

#ifdef HAVE_PWD_H
#include <pwd.h>
#endif
#ifdef HAVE_GRP_H
#include <grp.h>
#endif
#if APR_HAVE_UNISTD_H
#include <unistd.h>
#endif

APLOG_USE_MODULE(core);

#if AP_ENABLE_EXCEPTION_HOOK
APR_HOOK_STRUCT(
    APR_HOOK_LINK(fatal_exception)
    APR_HOOK_LINK(monitor)
    APR_HOOK_LINK(drop_privileges)
    APR_HOOK_LINK(mpm)
    APR_HOOK_LINK(mpm_query)
    APR_HOOK_LINK(mpm_note_child_killed)
    APR_HOOK_LINK(mpm_register_timed_callback)
    APR_HOOK_LINK(mpm_get_name)
)
AP_IMPLEMENT_HOOK_RUN_ALL(int, fatal_exception,
                          (ap_exception_info_t *ei), (ei), OK, DECLINED)
#else
APR_HOOK_STRUCT(
    APR_HOOK_LINK(monitor)
    APR_HOOK_LINK(drop_privileges)
    APR_HOOK_LINK(mpm)
    APR_HOOK_LINK(mpm_query)
    APR_HOOK_LINK(mpm_note_child_killed)
    APR_HOOK_LINK(mpm_register_timed_callback)
    APR_HOOK_LINK(mpm_get_name)
)
#endif
AP_IMPLEMENT_HOOK_RUN_ALL(int, monitor,
                          (apr_pool_t *p, server_rec *s), (p, s), OK, DECLINED)
AP_IMPLEMENT_HOOK_RUN_ALL(int, drop_privileges,
                          (apr_pool_t * pchild, server_rec * s),
                          (pchild, s), OK, DECLINED)
AP_IMPLEMENT_HOOK_RUN_FIRST(int, mpm,
                            (apr_pool_t *pconf, apr_pool_t *plog, server_rec *s),
                            (pconf, plog, s), DECLINED)
AP_IMPLEMENT_HOOK_RUN_FIRST(int, mpm_query,
                            (int query_code, int *result, apr_status_t *_rv),
                            (query_code, result, _rv), DECLINED)
AP_IMPLEMENT_HOOK_RUN_FIRST(apr_status_t, mpm_note_child_killed,
                            (int childnum),
                            (childnum), APR_ENOTIMPL)
AP_IMPLEMENT_HOOK_RUN_FIRST(apr_status_t, mpm_register_timed_callback,
                            (apr_time_t t, ap_mpm_callback_fn_t *cbfn, void *baton),
                            (t, cbfn, baton), APR_ENOTIMPL)
AP_IMPLEMENT_HOOK_RUN_FIRST(const char *, mpm_get_name,
                            (void),
                            (), NULL)

/* number of calls to wait_or_timeout between writable probes */
#ifndef INTERVAL_OF_WRITABLE_PROBES
#define INTERVAL_OF_WRITABLE_PROBES 10
#endif
static int wait_or_timeout_counter;

void ap_wait_or_timeout(apr_exit_why_e *status, int *exitcode, apr_proc_t *ret,
                        apr_pool_t *p, server_rec *s)
{
    apr_status_t rv;

    ++wait_or_timeout_counter;
    if (wait_or_timeout_counter == INTERVAL_OF_WRITABLE_PROBES) {
        wait_or_timeout_counter = 0;
        ap_run_monitor(p, s);
    }

    rv = apr_proc_wait_all_procs(ret, exitcode, status, APR_NOWAIT, p);
    if (APR_STATUS_IS_EINTR(rv)) {
        ret->pid = -1;
        return;
    }

    if (APR_STATUS_IS_CHILD_DONE(rv)) {
        return;
    }

    apr_sleep(1000000);
    ret->pid = -1;
    return;
}

#if defined(TCP_NODELAY)
void ap_sock_disable_nagle(apr_socket_t *s)
{
    /* The Nagle algorithm says that we should delay sending partial
     * packets in hopes of getting more data.  We don't want to do
     * this; we are not telnet.  There are bad interactions between
     * persistent connections and Nagle's algorithm that have very severe
