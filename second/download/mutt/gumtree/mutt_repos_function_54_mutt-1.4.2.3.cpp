static int _set_pgp_flags (HEADER *cur)
{
  int flags = 0;
  
  if (option (OPTPGPREPLYENCRYPT) && cur && cur->pgp & PGPENCRYPT)
    flags |= PGPENCRYPT;
  if (option (OPTPGPREPLYSIGN) && cur && cur->pgp & PGPSIGN)
    flags |= PGPSIGN;
  if (option (OPTPGPREPLYSIGNENCRYPTED) && cur && cur->pgp & PGPENCRYPT)
    flags |= PGPSIGN;

  return flags;

}