{
      width = (long)vto[p->width].data.num.as_signed;
      param_num++; /* since the width is extracted from a parameter, we
                      must skip that to get to the next one properly */
      if(width < 0) {
        /* "A negative field width is taken as a '-' flag followed by a
           positive field width." */
        width = -width;
        p->flags |= FLAGS_LEFT;
        p->flags &= ~FLAGS_PAD_NIL;
      }
    }