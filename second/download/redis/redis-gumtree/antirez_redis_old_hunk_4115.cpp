            dictAdd(c->db->dict,key,val);
        }
        addReply(c,shared.ok);
    } else {
        addReplySds(c,sdsnew(
            "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>|SWAPIN <key>|SWAPOUT <key>|RELOAD]\r\n"));
