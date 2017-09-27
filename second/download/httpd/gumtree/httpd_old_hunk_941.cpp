
    if (!strcmp(dash_k_arg, "graceful")) {
        if (!running) {
            printf("httpd not running, trying to start\n");
        }
        else {
            *exit_status = send_signal(otherpid, SIGUSR1);
            return 1;
        }
    }

    return 0;
}

void ap_mpm_rewrite_args(process_rec *process)
{
    apr_array_header_t *mpm_new_argv;
