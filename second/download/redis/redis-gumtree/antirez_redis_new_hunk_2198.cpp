            if (strlen(value) && access(value,X_OK) == -1) {
                addReplyError(c,
                    "Notification script seems non existing or non executable");
                if (changes) sentinelFlushConfig();
                return;
            }
            sdsfree(ri->notification_script);
