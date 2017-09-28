        } else if (!strcmp(reply2->str,"zset")) {
            sizecmd = "ZCARD";
            type = TYPE_ZSET;
        } else if (!strcmp(reply2->str,"none")) {
            freeReplyObject(reply1);
            freeReplyObject(reply2);
            continue;
        } else {
            fprintf(stderr, "Unknown key type '%s' for key '%s'\n",
                reply2->str, reply1->str);
            exit(1);
        }
