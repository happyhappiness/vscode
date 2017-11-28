        perror(logfile);
        fprintf(stderr, "         messages will be sent to 'stderr'.\n");
        fflush(stderr);
        debug_log = stderr;
    }

#if _SQUID_WINDOWS_
    setmode(fileno(debug_log), O_TEXT);
#endif
}

#if HAVE_SYSLOG
#ifdef LOG_LOCAL4

