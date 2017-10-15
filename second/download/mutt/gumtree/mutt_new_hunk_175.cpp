    mutt_error _("You already have an alias defined with that name!");
    return;
  }
  
  if (mutt_check_alias_name (buf, fixed, sizeof (fixed)))
  {
    switch (mutt_yesorno (_("Warning: This alias name may not work.  Fix it?"), MUTT_YES))
    {
      case MUTT_YES:
      	strfcpy (buf, fixed, sizeof (buf));
	goto retry_name;
      case -1: 
	return;
    }
  }
