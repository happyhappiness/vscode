{
      const char *v;
      unsigned int i = 0;

      for(v=value; *v && (i<len); v++,i++)
        {
          if (!isprint((unsigned char)*v))
            RETURN(E_BAD_ARGUMENT);
        }
    }