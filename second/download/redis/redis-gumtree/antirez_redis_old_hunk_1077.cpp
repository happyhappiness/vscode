                "Impossible to lock %s: %s", filename, strerror(errno));
        }
        close(fd);
        return REDIS_ERR;
    }
    /* Lock acquired: leak the 'fd' by not closing it, so that we'll retain the
     * lock to the file as long as the process exists. */
#endif /* __sun */

    return REDIS_OK;
}

void clusterInit(void) {
