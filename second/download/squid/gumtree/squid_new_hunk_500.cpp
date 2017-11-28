        return 1;
    }
    memcpy(nargs,argv+nstart+1,(nend-nstart)*sizeof(char *));
    nargs[nend-nstart]=NULL;
    if (debug) {
        fprintf(stderr, "%s| %s: NTLM command: ", LogTime(), PROGRAM);
        for (int i=0; i<nend-nstart; ++i)
            fprintf(stderr, "%s ", nargs[i]);
        fprintf(stderr, "\n");
    }
    if ((kargs = (char **)xmalloc((kend-kstart+1)*sizeof(char *))) == NULL) {
        fprintf(stderr, "%s| %s: Error allocating memory for kerberos helper\n", LogTime(), PROGRAM);
        return 1;
    }
    memcpy(kargs,argv+kstart+1,(kend-kstart)*sizeof(char *));
    kargs[kend-kstart]=NULL;
    if (debug) {
        fprintf(stderr, "%s| %s: Kerberos command: ", LogTime(), PROGRAM);
        for (int i=0; i<kend-kstart; ++i)
            fprintf(stderr, "%s ", kargs[i]);
        fprintf(stderr, "\n");
    }
    /*
       Fork Kerberos helper and NTLM helper and manage IO to send NTLM requests
       to the right helper. squid must keep session state
