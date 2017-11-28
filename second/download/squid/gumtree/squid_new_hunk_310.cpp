
        if (put_fd < 0) {
            fprintf(stderr, "%s: can't open file (%s)\n", argv[0],
                    xstrerror());
            exit(-1);
        }
#if _SQUID_WINDOWS_
        setmode(put_fd, O_BINARY);
#endif

        if (fstat(put_fd, &sb) < 0) {
            fprintf(stderr, "%s: can't identify length of file (%s)\n", argv[0], xstrerror());
        }
    }

    if (!host) {
        char *newhost = strstr(url, "://");
        if (newhost) {
            char *t;
            newhost += 3;
            newhost = xstrdup(newhost);
            t = newhost + strcspn(newhost, "@/?");
            if (*t == '@') {
                newhost = t + 1;
                t = newhost + strcspn(newhost, "@/?");
            }
            *t = '\0';
