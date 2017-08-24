f(t != NULL) {
    t = Curl_splay(i, t);
    if(compare(i, t->key)==0) {
      /* There already exists a node in the tree with the very same key. Build
         a doubly-linked circular list of nodes. We add the new 'node' struct
         to the end of this list. */

      node->key = KEY_NOTUSED; /* we set the key in the sub node to NOTUSED
                               to quickly identify this node as a subnode */
      node->samen = t;
      node->samep = t->samep;
      t->samep->samen = node;
      t->samep = node;

      return t; /* the root node always stays the same */
    }
  }