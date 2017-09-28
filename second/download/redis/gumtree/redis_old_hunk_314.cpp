    } else {
        long bytes = end-start+1;

        addReplyLongLong(c,redisPopcount(p+start,bytes));
    }
}
