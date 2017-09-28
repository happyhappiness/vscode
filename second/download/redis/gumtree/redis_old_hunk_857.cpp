                    &count, NULL) != C_OK) return;
                if (count <= 0) {
                    addReplyError(c,"COUNT must be > 0");
                    return;
                }
                i++;
            } else if (!strcasecmp(arg, "store") && (i+1) < remaining) {
                storekey = c->argv[base_args+i+1];
                storedist = 0;
                i++;
            } else if (!strcasecmp(arg, "storedist") && (i+1) < remaining) {
                storekey = c->argv[base_args+i+1];
                storedist = 1;
                i++;
            } else {
                addReply(c, shared.syntaxerr);
                return;
