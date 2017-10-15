  for (idx = 0, uid = key->uids; uid; idx++, uid = uid->next)
    {
      if (uid->revoked)
        continue;

      s = uid->uid;
      fputs (idx ? _(" aka ......: ") :_("Name ......: "), fp);
      if (uid->invalid)
        {
          fputs (_("[Invalid]"), fp);
          putc (' ', fp);
        }
