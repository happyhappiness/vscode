         (c->replytype == REPLY_BULK)) && c->readlen != -1 &&
          (unsigned)c->readlen <= sdslen(c->ibuf))
    {
        if (c->replytype == REPLY_BULK) {
            clientDone(c);
        } else if (c->replytype == REPLY_MBULK) {
            if (--c->mbulk == 0) {
                clientDone(c);
            } else {
