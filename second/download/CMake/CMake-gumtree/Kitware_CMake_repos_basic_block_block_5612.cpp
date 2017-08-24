f(compare(i, t->key) < 0) {
    node->smaller = t->smaller;
    node->larger = t;
    t->smaller = NULL;

  }