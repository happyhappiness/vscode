lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",
                     withscores ? (rangelen*2) : rangelen);