            /* Optimization: if the buffer contanins JUST our bulk element
             * instead of creating a new object by *copying* the sds we
             * just use the current sds string. */
#ifdef REDIS_MBULK_BIG_ARG
            if (pos == 0 &&
                c->bulklen >= REDIS_MBULK_BIG_ARG &&
                (signed) sdslen(c->querybuf) == c->bulklen+2)
            {
                // printf("HERE (arg %d)\n",c->argc);
