                zfree(slots);
                return;
            }
            if (server.cluster.slots[slot]) {
                addReplyErrorFormat(c,"Slot %lld is already busy", slot);
                zfree(slots);
                return;
