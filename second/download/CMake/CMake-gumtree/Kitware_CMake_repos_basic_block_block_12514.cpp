(rmode & 4)
      {
        tm->tm_sec++;
        t = mktime(tm);
      }