{
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