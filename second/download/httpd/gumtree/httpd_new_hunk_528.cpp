            CloseHandle(hPipeWrite);
            CloseHandle(hPipeRead);
            CloseHandle(hNullOutput);
            return -1;
        }
        else if (hShareError == INVALID_HANDLE_VALUE) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf,
                         "Parent: Failed to share error log with child.\n");
            CloseHandle(hPipeWrite);
            CloseHandle(hPipeRead);
            CloseHandle(hNullOutput);
            return -1;
        }
