sdscatprintf(sdsempty(),"$%lu\r\n",
                (unsigned long) stringObjectLen(argv[j]));