{
        if (best.base == -1 || cur.len > best.len)
          best = cur;
        cur.base = -1;
      }