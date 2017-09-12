            *score = scoreval;
        }
        if (isnan(*score)) {
            addReplySds(c,
                sdsnew("-ERR resulting score is not a number (NaN)\r\n"));
            zfree(score);
            /* Note that we don't need to check if the zset may be empty and
             * should be removed here, as we can only obtain Nan as score if
