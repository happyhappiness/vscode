            fprintf(stderr, "RANDOMKEY error: %s\n",
                reply1->str);
            exit(1);
        }
        /* Get the key type */
        reply2 = redisCommand(context,"TYPE %s",reply1->str);
        assert(reply2 && reply2->type == REDIS_REPLY_STATUS);
