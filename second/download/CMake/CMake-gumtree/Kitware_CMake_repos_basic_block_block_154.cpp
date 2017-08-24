{
      int i;
      for(i=0; i<len; i++, p++)
        {
          if (*p==pad) 
            *p = C_BLANK;
        }
    }