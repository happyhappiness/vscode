{
    node->larger = t->larger;
    node->smaller = t;
    t->larger = NULL;
  }