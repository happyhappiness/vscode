        if (msg != NULL) {
            addReplyError(c,(char*)msg);
        } else {
            addReplyError(c,"value is not a double");
        }
        return REDIS_ERR;
    }
