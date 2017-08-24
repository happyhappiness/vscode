{
    char *newp;
    size_t j, i;

    /* Otherwise, drop / and the first character (i.e., item type) ... */
    newp = path;
    newp+=2;

    /* ... then turn ? into TAB for search servers, Veronica, etc. ... */
    j = strlen(newp);
    for(i=0; i<j; i++)
      if(newp[i] == '?')
        newp[i] = '\x09';

    /* ... and finally unescape */
    result = Curl_urldecode(data, newp, 0, &sel, &len, FALSE);
    if(result)
      return result;
    sel_org = sel;
  }