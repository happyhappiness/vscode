            addReplyErrorFormat(c,"Target instance replied with error: %s",
                (buf1[0] == '-') ? buf1+1 : buf2+1);
        } else {
            dbDelete(c->db,c->argv[3]);
            addReply(c,shared.ok);
        }
    }

