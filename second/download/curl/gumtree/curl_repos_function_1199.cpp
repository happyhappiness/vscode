struct Curl_tree *Curl_splayinsert(struct timeval i,
                                   struct Curl_tree *t,
                                   struct Curl_tree *node)
{
  static const struct timeval KEY_NOTUSED = {-1,-1}; /* will *NEVER* appear */

  if(node == NULL)
    return t;

  if(t != NULL) {
    t = Curl_splay(i,t);
    if(compare(i, t->key)==0) {
      /* There already exists a node in the tree with the very same key. Build
         a linked list of nodes. We make the new 'node' struct the new master
         node and make the previous node the first one in the 'same' list. */

      node->same = t;
      node->key = i;
      node->smaller = t->smaller;
      node->larger = t->larger;

      t->smaller = node; /* in the sub node for this same key, we use the
                            smaller pointer to point back to the master
                            node */

      t->key = KEY_NOTUSED; /* and we set the key in the sub node to NOTUSED
                               to quickly identify this node as a subnode */

      return node; /* new root node */
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

  node->same = NULL; /* no identical node (yet) */
  return node;
}