            rangelen = (end-start)+1;

            /* Return the result */
            addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",rangelen));
            range = sdsnewlen((char*)o->ptr+start,rangelen);
            addReplySds(c,range);
            addReply(c,shared.crlf);
