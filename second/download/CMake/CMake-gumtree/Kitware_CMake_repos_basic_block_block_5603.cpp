{
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