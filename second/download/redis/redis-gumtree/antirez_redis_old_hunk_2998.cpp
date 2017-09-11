            /* Optimization: if the buffer contanins JUST our bulk element
             * instead of creating a new object by *copying* the sds we
             * just use the current sds string. */
            if (pos == 0 &&
                /* sdslen(c->querybuf) > 4096 && */
                (signed) sdslen(c->querybuf) == c->bulklen+2)
            {
                // printf("HERE (arg %d)\n",c->argc);
