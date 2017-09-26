                     "Parent: Could not create exit event for child process");
        apr_pool_destroy(ptemp);
        CloseHandle(waitlist[waitlist_ready]);
        return -1;
    }

    /* Build the env array */
    for (envc = 0; _environ[envc]; ++envc) {
        ;
    }
    env = apr_palloc(ptemp, (envc + 2) * sizeof (char*));  
    memcpy(env, _environ, envc * sizeof (char*));
    apr_snprintf(pidbuf, sizeof(pidbuf), "AP_PARENT_PID=%i", parent_pid);
    env[envc] = pidbuf;
    env[envc + 1] = NULL;

    rv = apr_proc_create(&new_child, cmd, args, env, attr, ptemp);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                     "Parent: Failed to create the child process.");
        apr_pool_destroy(ptemp);
        CloseHandle(hExitEvent);
        CloseHandle(waitlist[waitlist_ready]);
        CloseHandle(new_child.hproc);
        return -1;
    }
    apr_file_close(child_out);
    ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                 "Parent: Created child process %d", new_child.pid);

    if (send_handles_to_child(ptemp, waitlist[waitlist_ready], hExitEvent,
                              start_mutex, ap_scoreboard_shm,
                              new_child.hproc, new_child.in)) {
        /*
         * This error is fatal, mop up the child and move on
         * We toggle the child's exit event to cause this child 
         * to quit even as it is attempting to start.
         */
        SetEvent(hExitEvent);
        apr_pool_destroy(ptemp);
        CloseHandle(hExitEvent);
        CloseHandle(waitlist[waitlist_ready]);
        CloseHandle(new_child.hproc);
        return -1;
    }

    /* Important:
     * Give the child process a chance to run before dup'ing the sockets.
     * We have already set the listening sockets noninheritable, but if 
     * WSADuplicateSocket runs before the child process initializes
     * the listeners will be inherited anyway.
     */
    waitlist[waitlist_term] = new_child.hproc;
    rv = WaitForMultipleObjects(2, waitlist, FALSE, INFINITE);
    CloseHandle(waitlist[waitlist_ready]);
    if (rv != WAIT_OBJECT_0) {
        /* 
         * Outch... that isn't a ready signal. It's dead, Jim!
         */
        SetEvent(hExitEvent);
        apr_pool_destroy(ptemp);
        CloseHandle(hExitEvent);
        CloseHandle(new_child.hproc);
        return -1;
    }

    if (send_listeners_to_child(ptemp, new_child.pid, new_child.in)) {
        /*
         * This error is fatal, mop up the child and move on
         * We toggle the child's exit event to cause this child 
         * to quit even as it is attempting to start.
         */
        SetEvent(hExitEvent);
        apr_pool_destroy(ptemp);
        CloseHandle(hExitEvent);
        CloseHandle(new_child.hproc);
        return -1;
    }

    apr_file_close(new_child.in);

    *child_exit_event = hExitEvent;
    *child_proc = new_child.hproc;
    *child_pid = new_child.pid;

    return 0;
}

/***********************************************************************
 * master_main()
 * master_main() runs in the parent process.  It creates the child 
 * process which handles HTTP requests then waits on one of three 
 * events:
 *
 * restart_event
 * -------------
 * The restart event causes master_main to start a new child process and
 * tells the old child process to exit (by setting the child_exit_event).
 * The restart event is set as a result of one of the following:
 * 1. An apache -k restart command on the command line
 * 2. A command received from Windows service manager which gets 
 *    translated into an ap_signal_parent(SIGNAL_PARENT_RESTART)
 *    call by code in service.c.
 * 3. The child process calling ap_signal_parent(SIGNAL_PARENT_RESTART)
 *    as a result of hitting MaxRequestsPerChild.
 *
 * shutdown_event 
 * --------------
 * The shutdown event causes master_main to tell the child process to 
 * exit and that the server is shutting down. The shutdown event is
 * set as a result of one of the following:
 * 1. An apache -k shutdown command on the command line
 * 2. A command received from Windows service manager which gets
 *    translated into an ap_signal_parent(SIGNAL_PARENT_SHUTDOWN)
 *    call by code in service.c.
 *
 * child process handle
 * --------------------
 * The child process handle will be signaled if the child process 
 * exits for any reason. In a normal running server, the signaling
 * of this event means that the child process has exited prematurely
 * due to a seg fault or other irrecoverable error. For server
 * robustness, master_main will restart the child process under this 
 * condtion.
 *
 * master_main uses the child_exit_event to signal the child process
 * to exit.
 **********************************************************************/
#define NUM_WAIT_HANDLES 3
