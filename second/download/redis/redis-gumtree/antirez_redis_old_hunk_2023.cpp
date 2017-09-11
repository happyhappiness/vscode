        unsigned long rank;

        /* Find first element in range */
        zn = zslFirstInRange(zsl, range);

        /* Use rank of first element, if any, to determine preliminary count */
        if (zn != NULL) {
            rank = zslGetRank(zsl, zn->score, zn->obj);
            count = (zsl->length - (rank - 1));

            /* Find last element in range */
            zn = zslLastInRange(zsl, range);

            /* Use rank of last element, if any, to determine the actual count */
            if (zn != NULL) {
