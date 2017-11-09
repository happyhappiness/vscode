static const char *find_encoded_word (const char *s, const char **x)
{
  const char *p, *q;

  q = s;
  while ((p = strstr (q, "=?")))
  {
    for (q = p + 2;
	 0x20 < *q && *q < 0x7f && !strchr ("()<>@,;:\"/[]?.=", *q);
	 q++)
      ;
    if (q[0] != '?' || q[1] == '\0' || !strchr ("BbQq", q[1]) || q[2] != '?')
      continue;
    /* non-strict check since many MUAs will not encode spaces and question marks */
    for (q = q + 3; 0x20 <= *q && *q < 0x7f && (*q != '?' || q[1] != '='); q++)
      ;
    if (q[0] != '?' || q[1] != '=')
    {
      --q;
      continue;
    }

    *x = q + 2;
    return p;
  }

  return 0;
}