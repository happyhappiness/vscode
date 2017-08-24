f(!canpipe && check->inuse)
        /* this request can't be pipelined but the checked connection is
           already in use so we skip it */
        continue;