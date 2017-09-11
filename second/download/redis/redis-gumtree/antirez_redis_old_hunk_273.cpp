        goto end;
    }
    if (p == NULL) {
        anetSetError(err, "unable to bind socket");
        goto error;
    }

