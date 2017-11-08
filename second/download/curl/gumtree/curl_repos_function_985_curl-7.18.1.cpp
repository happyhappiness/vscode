static char * nss_no_password(PK11SlotInfo *slot, PRBool retry, void *arg)
{
  (void)slot; /* unused */
  (void)retry; /* unused */
  (void)arg; /* unused */
  return NULL;
}