            addReplyError(c,"Node config epoch is already non-zero");
        } else {
            myself->configEpoch = epoch;
            /* No need to fsync the config here since in the unlucky event
             * of a failure to persist the config, the conflict resolution code
             * will assign an unique config to this node. */
