                keys = zmalloc(sizeof(robj*)*1);
                numkeys = GetKeysInSlot(slot, keys, 1);
                zfree(keys);
                if (numkeys == 0) {
                    addReplyErrorFormat(c, "Can't assign hashslot %d to a different node while I still hold keys for this hash slot.", slot);
                    return;
                }
