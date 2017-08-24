(field->opts & O_NULLOK)
        {
          char *bp = field->buf;
          assert(bp != 0);
          while(is_blank(*bp))
            { bp++; }
          if (*bp == '\0') 
            return TRUE;
        }