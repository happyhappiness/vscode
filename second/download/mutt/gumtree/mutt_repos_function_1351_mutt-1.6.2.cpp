int mutt_needs_mailcap (BODY *m)
{
  switch (m->type)
  {
    case TYPETEXT:
      /* we can display any text, overridable by auto_view */
      return 0;
      break;

    case TYPEAPPLICATION:
      if((WithCrypto & APPLICATION_PGP) && mutt_is_application_pgp(m))
	return 0;
      if((WithCrypto & APPLICATION_SMIME) && mutt_is_application_smime(m))
	return 0;
      break;

    case TYPEMULTIPART:
    case TYPEMESSAGE:
      return 0;
  }

  return 1;
}