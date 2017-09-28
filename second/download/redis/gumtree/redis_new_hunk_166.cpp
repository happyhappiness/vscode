            printf("I/O error\n");
            exit(1);
        } else if (reply->type == REDIS_REPLY_ERROR) {
            printf("ERROR: %s\n", reply->str);
            exit(1);
        } else {
            unsigned int j;

            cur = strtoull(reply->element[0]->str,NULL,10);
            for (j = 0; j < reply->element[1]->elements; j++)
                printf("%s\n", reply->element[1]->element[j]->str);
        }
        freeReplyObject(reply);
