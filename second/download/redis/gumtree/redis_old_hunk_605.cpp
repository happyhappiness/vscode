            /* auth-pass <password> */
            sdsfree(ri->auth_pass);
            ri->auth_pass = strlen(value) ? sdsnew(value) : NULL;
            changes++;
       } else if (!strcasecmp(option,"quorum")) {
            /* quorum <count> */
            if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0)
                goto badfmt;
            ri->quorum = ll;
            changes++;
        } else {
            addReplyErrorFormat(c,"Unknown option '%s' for SENTINEL SET",
                option);
            if (changes) sentinelFlushConfig();
            return;
        }
        sentinelEvent(REDIS_WARNING,"+set",ri,"%@ %s %s",option,value);
    }

    if (changes) sentinelFlushConfig();
    addReply(c,shared.ok);
    return;

