            }
        }
        apr_file_close(fpw);
    }
    if (!found && !(mask & APHTP_DELUSER)) {
        apr_file_printf(errfile, "Adding ");
        putline(ftemp, record);
    }
    else if (!found && (mask & APHTP_DELUSER)) {
        apr_file_printf(errfile, "User %s not found" NL, user);
        exit(0);
    }
    apr_file_printf(errfile, "password for user %s" NL, user);
