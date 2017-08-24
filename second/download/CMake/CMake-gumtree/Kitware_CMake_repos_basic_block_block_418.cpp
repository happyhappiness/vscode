{
      int cnt = 0;
      char **kp = (char **)0;
      int ccase, cunique;

      argp->kwds        = va_arg(*ap,char **);
      ccase             = va_arg(*ap,int);
      cunique           = va_arg(*ap,int);
      argp->checkcase   = ccase   ? TRUE : FALSE;
      argp->checkunique = cunique ? TRUE : FALSE;

      kp = argp->kwds;
      while( kp && (*kp++) ) cnt++;
      argp->count = cnt;
    }