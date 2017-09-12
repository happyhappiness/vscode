                /* Broadcast the failing node name to everybody */
                clusterSendFail(node->name);
                clusterUpdateState();
            }
        } else {
            /* If it's not in NOADDR state and we don't have it, we
