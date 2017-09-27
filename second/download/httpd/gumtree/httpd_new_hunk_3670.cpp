                                            SERVICE_RUNNING);

    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);

    if (success)
        fprintf(stderr, signal ? "The '%s' service has restarted.\n"
                               : "The '%s' service has stopped.\n",
                        mpm_display_name);
    else
        fprintf(stderr, signal ? "Failed to restart the '%s' service.\n"
                               : "Failed to stop the '%s' service.\n",
                        mpm_display_name);
}
