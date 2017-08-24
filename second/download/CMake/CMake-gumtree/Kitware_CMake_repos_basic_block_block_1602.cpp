(no >= min_no) {
          // If it could work, try it.
          if (nextch == '\0' || *reginput == nextch)
            if (regmatch(next))
              return (1);
          // Couldn't or didn't -- back up.
          no--;
          reginput = save + no;
        }