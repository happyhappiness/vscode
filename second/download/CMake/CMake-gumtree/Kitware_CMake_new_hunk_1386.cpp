    fprintf(logfile, "ADDR %s:%d freeaddrinfo(%p)\n",
            source, line, (void *)freethis);
}
#endif  /* CURLDEBUG */

/*
 * Curl_ipvalid() checks what CURL_IPRESOLVE_* requirements that might've
