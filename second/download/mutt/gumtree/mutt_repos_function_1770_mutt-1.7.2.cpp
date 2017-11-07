static int pgp_id_is_valid (pgp_uid_t *uid)
{
  if (!pgp_key_is_valid (uid->parent))
    return 0;
  if (uid->flags & KEYFLAG_CANTUSE)
    return 0;
  /* else */
  return 1;
}