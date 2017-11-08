struct Curl_tree *Curl_splaygetbest(struct timeval i,
                                    struct Curl_tree *t,
                                    struct Curl_tree **removed)
{
  struct Curl_tree *x;

  if(!t) {
    *removed = NULL; /* none removed since there was no root */
    return NULL;
  }

  t = Curl_splay(i,t);
  if(compare(i, t->key) < 0) {
    /* too big node, try the smaller chain */
    if(t->smaller)
      t=Curl_splay(t->smaller->key, t);
    else {
      /* fail */
      *removed = NULL;
      return t;
    }
  }

  if(compare(i, t->key) >= 0) {               /* found it */
    /* FIRST! Check if there is a list with identical keys */
    x = t->same;
    if(x) {
      /* there is, pick one from the list */

      /* 'x' is the new root node */

      x->key = t->key;
      x->larger = t->larger;
      x->smaller = t->smaller;

      *removed = t;
      return x; /* new root */
    }

    if(t->smaller == NULL) {
      x = t->larger;
    }
    else {
      x = Curl_splay(i, t->smaller);
      x->larger = t->larger;
    }
    *removed = t;

    return x;
  }
  else {
    *removed = NULL; /* no match */
    return t;        /* It wasn't there */
  }
}