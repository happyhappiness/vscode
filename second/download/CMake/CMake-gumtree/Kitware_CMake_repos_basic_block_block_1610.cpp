{

          //
          // Don't set endp if some later invocation of the
          // same parentheses already has.
          //
          if (regendp[no] == 0)
            regendp[no] = save;
          return (1);
        }