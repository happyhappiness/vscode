_snprintf(cp->ErrorMessage, CMPE_PIPE_BUFFER_SIZE,
                "Process execution failed with error 0x%X.  "
                "FormatMessage failed with error 0x%X.",
                original, GetLastError());