        if (reclaim_one_pid(cur_extra->pid, DO_NOTHING)) {
            AP_DEBUG_ASSERT(1 == ap_unregister_extra_mpm_process(cur_extra->pid));
        }
        cur_extra = next;
    }
}
#endif /* AP_MPM_WANT_RECLAIM_CHILD_PROCESSES */

#ifdef AP_MPM_WANT_WAIT_OR_TIMEOUT

/* number of calls to wait_or_timeout between writable probes */
#ifndef INTERVAL_OF_WRITABLE_PROBES
