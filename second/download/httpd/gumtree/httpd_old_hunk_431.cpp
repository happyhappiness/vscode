                     "Child %d: Child process is exiting", my_pid);        
        return 1;
    }
    else 
    {
        /* A real-honest to goodness parent */

        restart = master_main(ap_server_conf, shutdown_event, restart_event);

        if (!restart) 
        {
            /* Shutting down. Clean up... */
