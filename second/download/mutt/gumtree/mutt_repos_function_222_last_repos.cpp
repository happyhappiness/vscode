static void pipe_set_flags (int decode, int print, int *cmflags, int *chflags)
{
  if (decode)
  {
    *cmflags |= MUTT_CM_DECODE | MUTT_CM_CHARCONV;
    *chflags |= CH_DECODE | CH_REORDER;
    
    if (option (OPTWEED))
    {
      *chflags |= CH_WEED;
      *cmflags |= MUTT_CM_WEED;
    }
  }
  
  if (print)
    *cmflags |= MUTT_CM_PRINTING;
  
}