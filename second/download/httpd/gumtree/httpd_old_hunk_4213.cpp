                }
                next = next->next;
            }
        }
    }
    else {
        fname = "none";
    }

    /* first try to attach to existing shared memory */
    fbased = (name != NULL);
    if (fbased) {
        rv = apr_shm_attach(&shm, fname, gpool);
    }
    else {
        rv = APR_EINVAL;
    }
