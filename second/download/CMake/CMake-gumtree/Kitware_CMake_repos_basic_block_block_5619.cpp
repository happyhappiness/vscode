{
      x = Curl_splay(removenode->key, t->smaller);
      x->larger = t->larger;
    }