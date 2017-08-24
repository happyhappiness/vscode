{
    /* 'x' is the new root node, we just make it use the root node's
       smaller/larger links */

    x->key = t->key;
    x->larger = t->larger;
    x->smaller = t->smaller;
    x->samep = t->samep;
    t->samep->samen = x;
  }