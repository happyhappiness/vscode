sprintf(current_time, "%04d-%02d-%02d %02d:%02d:%02d",
      t->tm_year + 1900,
      t->tm_mon + 1,
      t->tm_mday,
      t->tm_hour,
      t->tm_min,
      t->tm_sec);