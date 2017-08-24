r(le = l->head; le; le = le->next) {
      he = le->ptr;
      if(h->comp_func(he->key, he->key_len, key, key_len)) {
        return he->ptr;
      }
    }