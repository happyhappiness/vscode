{
        /* "A negative field width is taken as a '-' flag followed by a
           positive field width." */
        width = -width;
        p->flags |= FLAGS_LEFT;
        p->flags &= ~FLAGS_PAD_NIL;
      }