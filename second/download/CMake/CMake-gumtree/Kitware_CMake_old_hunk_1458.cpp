	_stricmp(comshell, "command.com") != 0) 
      {
      /* NT/2000 and not using command.com. */
      x = i + strlen(s3) + strlen(cmdstring) + 1;
      s2 = (char *)_alloca(x);
      ZeroMemory(s2, x);
      sprintf(s2, "%s%s%s", s1, s3, cmdstring);
