        }
    }

    /* Stats */
    if (allsections || defsections || !strcasecmp(section,"stats")) {
        if (sections++) info = sdscat(info,"\r\n");
