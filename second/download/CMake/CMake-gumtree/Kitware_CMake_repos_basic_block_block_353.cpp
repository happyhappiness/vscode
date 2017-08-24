{
      typedef int (*Generic_Method)(int (* const)(FORM *),FORM *);
      static const Generic_Method Generic_Methods[] = 
        {
          Page_Navigation,         /* overloaded to call field&form hooks */
          Inter_Field_Navigation,  /* overloaded to call field hooks      */
          NULL,                    /* Intra-Field is generic              */
          Vertical_Scrolling,      /* Overloaded to check multi-line      */
          Horizontal_Scrolling,    /* Overloaded to check single-line     */
          Field_Editing,           /* Overloaded to mark modification     */
          NULL,                    /* Edit Mode is generic                */
          NULL,                    /* Field Validation is generic         */
          NULL                     /* Choice Request is generic           */
        };
      size_t nMethods = (sizeof(Generic_Methods)/sizeof(Generic_Methods[0]));
      size_t method   = ((BI->keycode & ID_Mask) >> ID_Shft) & 0xffff;
      
      if ( (method >= nMethods) || !(BI->cmd) )
        res = E_SYSTEM_ERROR;
      else
        {
          Generic_Method fct = Generic_Methods[method];
          if (fct)
            res = fct(BI->cmd,form);
          else
            res = (BI->cmd)(form);
        }
    }