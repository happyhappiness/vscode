static int pgp_id_matches_addr (ADDRESS *addr, ADDRESS *u_addr, pgp_uid_t *uid)
{
  int rv = 0;

  if (pgp_id_is_valid (uid))
    rv |= PGP_KV_VALID;

  if (pgp_id_is_strong (uid))
    rv |= PGP_KV_STRONGID;

  if (addr->mailbox && u_addr->mailbox
      && mutt_strcasecmp (addr->mailbox, u_addr->mailbox) == 0)
    rv |= PGP_KV_ADDR;

  if (addr->personal && u_addr->personal
      && mutt_strcasecmp (addr->personal, u_addr->personal) == 0)
    rv |= PGP_KV_STRING;

  return rv;
}