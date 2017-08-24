{
    t = 0;
    if (i == 3)
      t = rar->mtime;
    rmode = flags >> i * 4;
    if (rmode & 8)
    {
      if (!t)
      {
        if (p + 4 > endp)
          return (-1);
        ttime = archive_le32dec(p);
        t = get_time(ttime);
        p += 4;
      }
      rem = 0;
      count = rmode & 3;
      if (p + count > endp)
        return (-1);
      for (j = 0; j < count; j++)
      {
        rem = ((*p) << 16) | (rem >> 8);
        p++;
      }
      tm = localtime(&t);
      nsec = tm->tm_sec + rem / NS_UNIT;
      if (rmode & 4)
      {
        tm->tm_sec++;
        t = mktime(tm);
      }
      if (i == 3)
      {
        rar->mtime = t;
        rar->mnsec = nsec;
      }
      else if (i == 2)
      {
        rar->ctime = t;
        rar->cnsec = nsec;
      }
      else if (i == 1)
      {
        rar->atime = t;
        rar->ansec = nsec;
      }
      else
      {
        rar->arctime = t;
        rar->arcnsec = nsec;
      }
    }
  }