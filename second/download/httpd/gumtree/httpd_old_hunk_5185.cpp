            apr_shm_remove(fname, gpool);
            rv = apr_shm_create(&shm, size, fname, gpool);
        }
        else {
            rv = apr_shm_create(&shm, size, NULL, gpool);
        }
        if (rv != APR_SUCCESS) {
            return rv;
        }
        if (fbased) {
            /* Set permissions to shared memory
             * so it can be attached by child process
