{
      /* the new expire time was later so just add it to the queue
         and get out */
      multi_addtimeout(data, &set, id);
      return;
    }