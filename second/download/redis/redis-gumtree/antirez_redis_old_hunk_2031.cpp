            /* Recompute it and update the cached value. */
            card = hllCount(hdr,&invalid);
            if (invalid) {
                addReplyError(c,invalid_hll_err);
                return;
            }
            hdr->card[0] = card & 0xff;
