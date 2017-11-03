static crypt_key_t *crypt_getkeybyaddr (ADDRESS * a, short abilities,
					unsigned int app, int *forced_valid,
					int oppenc_mode)
{
  ADDRESS *r, *p;
  LIST *hints = NULL;

  int weak    = 0;
  int invalid = 0;
  int addr_match = 0;
  int multi   = 0;
  int this_key_has_strong;
  int this_key_has_addr_match;
  int this_key_has_weak;
  int this_key_has_invalid;
  int match;

  crypt_key_t *keys, *k;
  crypt_key_t *the_strong_valid_key = NULL;
  crypt_key_t *a_valid_addrmatch_key = NULL;
  crypt_key_t *matches = NULL;
  crypt_key_t **matches_endp = &matches;
  
  *forced_valid = 0;

  if (a && a->mailbox)
    hints = crypt_add_string_to_hints (hints, a->mailbox);
  if (a && a->personal)
    hints = crypt_add_string_to_hints (hints, a->personal);

  if (! oppenc_mode )
    mutt_message (_("Looking for keys matching \"%s\"..."), a->mailbox);
  keys = get_candidates (hints, app, (abilities & KEYFLAG_CANSIGN) );

  mutt_free_list (&hints);
  
  if (!keys)
    return NULL;
  
  dprint (5, (debugfile, "crypt_getkeybyaddr: looking for %s <%s>.",
	      a->personal, a->mailbox));

  for (k = keys; k; k = k->next)
    {
      dprint (5, (debugfile, "  looking at key: %s `%.15s'\n",
                  crypt_keyid (k), k->uid));
      
      if (abilities && !(k->flags & abilities))
        {
          dprint (5, (debugfile, "  insufficient abilities: Has %x, want %x\n",
                      k->flags, abilities));
          continue;
        }

      this_key_has_weak    = 0;	/* weak but valid match   */
      this_key_has_invalid = 0;   /* invalid match          */
      this_key_has_strong  = 0;	/* strong and valid match */
      this_key_has_addr_match = 0;
      match                = 0;   /* any match 		  */

      r = rfc822_parse_adrlist (NULL, k->uid);
      for (p = r; p; p = p->next)
        {
          int validity = crypt_id_matches_addr (a, p, k);
              
          if (validity & CRYPT_KV_MATCH)	/* something matches */
          {
            match = 1;

            if (validity & CRYPT_KV_VALID)
            {
              if (validity & CRYPT_KV_ADDR)
              {
                if (validity & CRYPT_KV_STRONGID)
                {
                  if (the_strong_valid_key
                      && the_strong_valid_key->kobj != k->kobj)
                    multi             = 1;
                  this_key_has_strong = 1;
                }
                else
                  this_key_has_addr_match = 1;
              }
              else
                this_key_has_weak = 1;
            }
            else
              this_key_has_invalid = 1;
          }
        }
      rfc822_free_address (&r);
      
      if (match)
        {
          crypt_key_t *tmp;

          *matches_endp = tmp = crypt_copy_key (k);
          matches_endp = &tmp->next;

          if (this_key_has_strong)
            the_strong_valid_key = tmp;
          else if (this_key_has_addr_match)
          {
            addr_match = 1;
            a_valid_addrmatch_key = tmp;
          }
          else if (this_key_has_invalid)
            invalid = 1;
          else if (this_key_has_weak)
            weak = 1;
        }
    }
  
  crypt_free_key (&keys);
  
  if (matches)
    {
      if (oppenc_mode)
        {
          if (the_strong_valid_key)
            k = crypt_copy_key (the_strong_valid_key);
          else if (a_valid_addrmatch_key)
            k = crypt_copy_key (a_valid_addrmatch_key);
          else
            k = NULL;
        }
      else if (the_strong_valid_key && !multi && !weak && !addr_match
          && !(invalid && option (OPTPGPSHOWUNUSABLE)))
        {	
          /* 
           * There was precisely one strong match on a valid ID, there
           * were no valid keys with weak matches, and we aren't
           * interested in seeing invalid keys.
           * 
           * Proceed without asking the user.
           */
          k = crypt_copy_key (the_strong_valid_key);
        }
      else 
        {
          /* 
           * Else: Ask the user.
           */
          k = crypt_select_key (matches, a, NULL, app, forced_valid);
        }

      crypt_free_key (&matches);
    }
  else 
    k = NULL;
  
  return k;
}