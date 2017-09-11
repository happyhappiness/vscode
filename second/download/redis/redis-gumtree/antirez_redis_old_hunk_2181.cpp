            }
            /* If this hash slot was served by 'myself' before to switch
             * make sure there are no longer local keys for this hash slot. */
            if (server.cluster->slots[slot] == server.cluster->myself &&
                n != server.cluster->myself)
            {
                if (countKeysInSlot(slot) != 0) {
                    addReplyErrorFormat(c, "Can't assign hashslot %d to a different node while I still hold keys for this hash slot.", slot);
                    return;
