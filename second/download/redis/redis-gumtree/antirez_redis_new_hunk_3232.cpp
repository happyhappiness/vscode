                zfree(slots);
                return;
            }
            if (del && server.cluster.slots[slot] == NULL) {
                addReplyErrorFormat(c,"Slot %lld is already unassigned", slot);
                zfree(slots);
                return;
            } else if (!del && server.cluster.slots[slot]) {
                addReplyErrorFormat(c,"Slot %lld is already busy", slot);
                zfree(slots);
                return;
