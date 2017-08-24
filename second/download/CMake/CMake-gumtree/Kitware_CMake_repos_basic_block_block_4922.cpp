f(data->easy_conn &&
         !(data->easy_conn->handler->flags & PROTOPT_DIRLOCK))
        /* set socket event bitmask if they're not locked */
        data->easy_conn->cselect_bits = ev_bitmask