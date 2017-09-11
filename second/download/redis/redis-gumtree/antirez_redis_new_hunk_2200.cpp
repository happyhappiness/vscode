            sdsfree(ri->auth_pass);
            ri->auth_pass = strlen(value) ? sdsnew(value) : NULL;
            changes++;
        } else {
            addReplyErrorFormat(c,"Unknown option '%s' for SENTINEL SET",
                option);
            if (changes) sentinelFlushConfig();
            return;
        }
    }

