        sprintf(buf,"%ld",aux);
        printf(" %-12s",buf);

        /* Children */
        aux = getLongInfoField(reply->str,"bgsave_in_progress");
        aux |= getLongInfoField(reply->str,"aof_rewrite_in_progress") << 1;
        switch(aux) {
        case 0: break;
        case 1:
            printf("SAVE");
            break;
        case 2:
            printf("AOF");
            break;
        case 3:
            printf("SAVE+AOF");
            break;
        }

        printf("\n");
        freeReplyObject(reply);
        usleep(config.interval);
    }
