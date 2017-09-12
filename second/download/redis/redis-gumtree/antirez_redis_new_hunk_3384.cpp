
        he = gethostbyname(addr);
        if (he == NULL) {
            anetSetError(err, "can't resolve: %s", addr);
            close(s);
            return ANET_ERR;
        }
