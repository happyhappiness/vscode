{
    /* there is, pick one from the list */

    /* 'x' is the new root node */

    x->key = t->key;
    x->larger = t->larger;
    x->smaller = t->smaller;
    x->samep = t->samep;
    t->samep->samen = x;

    *removed = t;
    return x; /* new root */
  }