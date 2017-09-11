        return;
    } else if ((c->argc - 2) % 3 != 0) {
        /* Need an odd number of arguments if we got this far... */
        addReplyError(c, "format is: geoadd [key] [lat1] [long1] [member1] "
                         "[lat2] [long2] [member2] ... ");
        return;
    }

