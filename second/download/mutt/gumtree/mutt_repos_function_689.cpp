static int crypt_id_matches_addr (ADDRESS *addr, ADDRESS *u_addr,
                                  crypt_key_t *key)
{
  int rv = 0;
  
  if (crypt_id_is_valid (key))
    rv |= CRYPT_KV_VALID;

  if (crypt_id_is_strong (key))
    rv |= CRYPT_KV_STRONGID;
  
  if (addr->mailbox && u_addr->mailbox
      && mutt_strcasecmp (addr->mailbox, u_addr->mailbox) == 0)
    rv |= CRYPT_KV_ADDR;
    
  if (addr->personal && u_addr->personal
      && mutt_strcasecmp (addr->personal, u_addr->personal) == 0)
    rv |= CRYPT_KV_STRING;
  
  return rv;
}