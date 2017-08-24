f(compare(i, t->larger->key) > 0) {
        y = t->larger;                          /* rotate larger */
        t->larger = y->smaller;
        y->smaller = t;
        t = y;
        if(t->larger == NULL)
          break;
      }