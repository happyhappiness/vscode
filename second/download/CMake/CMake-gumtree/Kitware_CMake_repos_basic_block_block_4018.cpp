r(le = (h->table[i])->head;
        le;
        le = le->next) {
      curl_hash_element *el = le->ptr;
      cb(user, el->ptr);
    }