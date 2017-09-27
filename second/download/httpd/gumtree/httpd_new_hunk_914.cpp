            if (!signal) {
                fprintf(stderr,"The %s service is not started.\n", mpm_display_name);
                return;
            }
        }

        fprintf(stderr,"The %s service is %s.\n", mpm_display_name,
               signal ? "restarting" : "stopping");

        apr_snprintf(prefix, sizeof(prefix), "ap%ld", (long)service_pid);
        setup_signal_names(prefix);

        if (!signal)
        {
            int ticks = 60;
            ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
            while (--ticks)
            {
                if (!IsWindow(hwnd)) {
