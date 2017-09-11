            /* Recompute it and update the cached value. */
            card = hllCount(hdr,&invalid);
            if (invalid) {
                addReplyError(c,"Invalid HLL object detected");
                return;
            }
            hdr->card[0] = card & 0xff;
