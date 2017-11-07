static int pgp_id_is_strong (pgp_uid_t *uid)
{
  if ((uid->trust & 3) < 3)
    return 0;
  /* else */
  return 1;
}