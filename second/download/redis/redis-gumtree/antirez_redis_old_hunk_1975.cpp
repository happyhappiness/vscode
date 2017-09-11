            addReplyError(c,"Node config epoch is already non-zero");
        } else {
            myself->configEpoch = epoch;
            if (server.cluster->currentEpoch < epoch)
                server.cluster->currentEpoch = epoch;
            /* No need to fsync the config here since in the unlucky event
