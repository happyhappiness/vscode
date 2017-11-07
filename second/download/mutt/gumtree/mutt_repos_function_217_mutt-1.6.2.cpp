static void pipe_set_flags (int decode, int print, int *cmflags, int *chflags)
{
  if (decode)
  {
    *cmflags |= M_CM_DECODE | M_CM_CHARCONV;
    *chflags |= CH_DECODE | CH_REORDER;
    
    if (option (OPTWEED))
    {
      *chflags |= CH_WEED;
      *cmflags |= M_CM_WEED;
    }
  }
  
  if (print)
    *cmflags |= M_CM_PRINTING;
  
}