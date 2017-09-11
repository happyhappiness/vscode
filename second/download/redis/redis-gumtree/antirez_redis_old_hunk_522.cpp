                addReplyError(c,
                    "When using MIGRATE KEYS option, the key argument"
                    " must be set to the empty string");
                zfree(ov); zfree(kv);
                return;
            }
            first_key = j+1;
            num_keys = c->argc - j - 1;
            ov = zrealloc(ov,sizeof(robj*)*num_keys);
            kv = zrealloc(kv,sizeof(robj*)*num_keys);
            break; /* All the remaining args are keys. */
        } else {
            addReply(c,shared.syntaxerr);
