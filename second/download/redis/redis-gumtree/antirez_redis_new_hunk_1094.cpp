                sort = SORT_DESC;
            } else if (!strcasecmp(arg, "count") && remaining > 0) {
                if (getLongLongFromObjectOrReply(c, c->argv[base_args+i+1],
                    &count, NULL) != C_OK) return;
                if (count <= 0) {
                    addReplyError(c,"COUNT must be > 0");
                    return;
