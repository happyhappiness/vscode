                keys->element[i]->str, context->err, context->errstr);
            exit(1);
        } else if(reply->type != REDIS_REPLY_STATUS) {
            fprintf(stderr, "Invalid reply type (%d) for TYPE on key '%s'!\n",
                reply->type, keys->element[i]->str);
            exit(1);
        }

