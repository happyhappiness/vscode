static char * nss_get_password(PK11SlotInfo * slot, PRBool retry, void *arg)
{
  pphrase_arg_t *parg;
  parg = (pphrase_arg_t *) arg;

  (void)slot; /* unused */
  if(retry > 2)
    return NULL;
  if(parg->data->set.str[STRING_KEY_PASSWD])
    return (char *)PORT_Strdup((char *)parg->data->set.str[STRING_KEY_PASSWD]);
  else
    return NULL;
}