{
  struct Curl_tree N, *l, *r, *y;
  long comp;

  if(t == NULL)
    return t;
  N.smaller = N.larger = NULL;
  l = r = &N;

  for(;;) {
    comp = compare(i, t->key);
    if(comp < 0) {
      if(t->smaller == NULL)
        break;
      if(compare(i, t->smaller->key) < 0) {
        y = t->smaller;                           /* rotate smaller */
        t->smaller = y->larger;
        y->larger = t;
        t = y;
        if(t->smaller == NULL)
          break;
      }
      r->smaller = t;                               /* link smaller */
      r = t;
      t = t->smaller;
    }
    else if(comp > 0) {
      if(t->larger == NULL)
        break;
      if(compare(i, t->larger->key) > 0) {
        y = t->larger;                          /* rotate larger */
        t->larger = y->smaller;
        y->smaller = t;
        t = y;
        if(t->larger == NULL)
          break;
      }
      l->larger = t;                              /* link larger */
      l = t;
      t = t->larger;
    }
    else
      break;
  }

  l->larger = t->smaller;                                /* assemble */
  r->smaller = t->larger;
  t->smaller = N.larger;
  t->larger = N.smaller;

  return t;
}