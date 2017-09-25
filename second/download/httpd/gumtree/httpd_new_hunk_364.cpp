            apr_strerror(rv, errbuf, sizeof(errbuf));
            exit(ERR_FILEPERM);
        }
        fprintf(stdout, "Database %s %s.\n", h->filename, 
                h->create ? "created" : (changed ? "modified" : "updated"));
    }
    if (cmd == HTDBM_NOFILE) {
        if (!need_cmnt) {
            fprintf(stderr, "%s:%s\n", h->username, h->userpass);
        }
        else {
            fprintf(stderr, "%s:%s:%s\n", h->username, h->userpass,
                    h->comment);
        }
    }
    htdbm_terminate(h);
    apr_terminate();
    
    return 0; /* Suppress compiler warning. */
}
