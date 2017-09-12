                *p = '\0';
                *(p-1) = '\0';
                c->readlen = atoi(c->ibuf+1)+2;
                // printf("BULK ATOI: %s\n", c->ibuf+1);
                /* Handle null bulk reply "$-1" */
                if (c->readlen-2 == -1) {
                    clientDone(c);
