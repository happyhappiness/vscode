static crypt_key_t *crypt_ask_for_key (char *tag, 
                                       char *whatfor, 
                                       short abilities,
				       unsigned int app,
                                       int *forced_valid)
{
  crypt_key_t *key;
  char resp[SHORT_STRING];
  struct crypt_cache *l = NULL;
  int dummy;

  if (!forced_valid)
    forced_valid = &dummy;

  mutt_clear_error ();

  *forced_valid = 0;
  resp[0] = 0;
  if (whatfor)
    {
      
      for (l = id_defaults; l; l = l->next)
        if (!mutt_strcasecmp (whatfor, l->what))
          {
            strfcpy (resp, NONULL (l->dflt), sizeof (resp));
            break;
          }
    }


  for (;;)
    {
      resp[0] = 0;
      if (mutt_get_field (tag, resp, sizeof (resp), MUTT_CLEAR) != 0)
        return NULL;
      
      if (whatfor)
        {
          if (l)
            mutt_str_replace (&l->dflt, resp);
          else
            {
              l = safe_malloc (sizeof (struct crypt_cache));
              l->next = id_defaults;
              id_defaults = l;
              l->what = safe_strdup (whatfor);
              l->dflt = safe_strdup (resp);
            }
        }
      
      if ((key = crypt_getkeybystr (resp, abilities, app, forced_valid)))
        return key;
      
      BEEP ();
    }
  /* not reached */
}