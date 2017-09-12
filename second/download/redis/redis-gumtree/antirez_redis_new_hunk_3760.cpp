            score += *(double*)dictGetEntryVal(de);

        if (isnan(score)) {
            addReplyError(c,"resulting score is not a number (NaN)");
            /* Note that we don't need to check if the zset may be empty and
             * should be removed here, as we can only obtain Nan as score if
             * there was already an element in the sorted set. */
