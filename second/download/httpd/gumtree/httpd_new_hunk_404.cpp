        else {
            fprintf(stderr, "%s:%s:%s\n", h->username, h->userpass,
                    h->comment);
        }
    }
    htdbm_terminate(h);
    
    return 0; /* Suppress compiler warning. */
}
