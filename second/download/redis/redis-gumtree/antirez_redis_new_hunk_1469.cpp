        return;
    } else if ((c->argc - 2) % 3 != 0) {
        /* Need an odd number of arguments if we got this far... */
        addReplyError(c, "format is: geoadd [key] [x1] [y1] [member1] "
                         "[x2] [y2] [member2] ... ");
        return;
    }

