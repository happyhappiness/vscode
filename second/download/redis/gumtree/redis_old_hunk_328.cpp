        } else {
            addReplyErrorFormat(c,"Unknown option '%s' for SENTINEL SET",
                option);
            if (changes) sentinelFlushConfig();
            return;
        }
    }

    if (changes) sentinelFlushConfig();
    addReply(c,shared.ok);
    return;

