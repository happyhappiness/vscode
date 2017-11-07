void pgp_extract_keys_from_attachment_list (FILE *fp, int tag, BODY *top)
{
  if(!fp)
  {
    mutt_error _("Internal error. Inform <roessler@guug.de>.");
    return;
  }

  mutt_endwin (NULL);
  set_option(OPTDONTHANDLEPGPKEYS);
  
  for(; top; top = top->next)
  {
    if(!tag || top->tagged)
      pgp_extract_keys_from_attachment (fp, top);
    
    if(!tag)
      break;
  }
  
  unset_option(OPTDONTHANDLEPGPKEYS);
}