{
      argn->precision = va_arg(*ap,int);
      argn->low       = va_arg(*ap,double);
      argn->high      = va_arg(*ap,double);
#if HAVE_LOCALE_H
      argn->L         = localeconv();
#else
      argn->L         = NULL;
#endif
    }