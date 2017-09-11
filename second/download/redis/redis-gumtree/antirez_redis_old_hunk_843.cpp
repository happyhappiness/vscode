        }

        /* Change the state and log the event. */
        serverLog(REDIS_WARNING,"Cluster state changed: %s",
            new_state == REDIS_CLUSTER_OK ? "ok" : "fail");
        server.cluster->state = new_state;
    }
