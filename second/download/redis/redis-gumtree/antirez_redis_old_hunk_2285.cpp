                        "Handshake error: we already know node %.40s, updating the address if needed.", sender->name);
                    if (nodeUpdateAddressIfNeeded(sender,link,ntohs(hdr->port)))
                    {
                        clusterUpdateState();
                        clusterSaveConfigOrDie();
                    }
                    /* Free this node as we alrady have it. This will
                     * cause the link to be freed as well. */
