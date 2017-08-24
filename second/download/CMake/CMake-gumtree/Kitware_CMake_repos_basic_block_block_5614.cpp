{
  static const struct timeval KEY_NOTUSED = {-1, -1}; /* will *NEVER* appear */

  if(node == NULL)
    return t;

  if(t != NULL) {
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

  if(t == NULL) {
    node->smaller = node->larger = NULL;
  }
  else if(compare(i, t->key) < 0) {
    node->smaller = t->smaller;
    node->larger = t;
    t->smaller = NULL;

  }
  else {
    node->larger = t->larger;
    node->smaller = t;
    t->larger = NULL;
  }
  node->key = i;

  /* no identical nodes (yet), we are the only one in the list of nodes */
  node->samen = node;
  node->samep = node;
  return node;
}