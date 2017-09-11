            /* Not enough data (+2 == trailing \r\n) */
            break;
        } else {
#ifdef REDIS_MBULK_BIG_ARG
            /* Optimization: if the buffer contanins JUST our bulk element
             * instead of creating a new object by *copying* the sds we
             * just use the current sds string. */
            if (pos == 0 &&
                c->bulklen >= REDIS_MBULK_BIG_ARG &&
                (signed) sdslen(c->querybuf) == c->bulklen+2)
            {
                // printf("HERE (arg %d)\n",c->argc);
                c->argv[c->argc++] = createObject(REDIS_STRING,c->querybuf);
                sdsIncrLen(c->querybuf,-2); /* remove CRLF */
                c->querybuf = sdsempty();
