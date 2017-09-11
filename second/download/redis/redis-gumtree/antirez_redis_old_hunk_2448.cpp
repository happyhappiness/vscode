                "FAIL message received from %.40s about %.40s",
                hdr->sender, hdr->data.fail.about.nodename);
            failing->flags |= REDIS_NODE_FAIL;
            failing->flags &= ~REDIS_NODE_PFAIL;
            clusterUpdateState();
            clusterSaveConfigOrDie();
