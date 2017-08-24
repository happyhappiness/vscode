{
        OUTCHAR('0');
        if(p->flags & FLAGS_UPPER)
          OUTCHAR('X');
        else
          OUTCHAR('x');
      }