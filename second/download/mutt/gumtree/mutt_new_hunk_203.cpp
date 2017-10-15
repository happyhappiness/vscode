        forced_valid = 0;
        k_info = NULL;

        if (crypt_hook != NULL)
          {
            crypt_hook_val = crypt_hook->data;
            r = MUTT_YES;
            if (! oppenc_mode && option(OPTCRYPTCONFIRMHOOK))
              {
                snprintf (buf, sizeof (buf), _("Use keyID = \"%s\" for %s?"),
                          crypt_hook_val, p->mailbox);
                r = mutt_yesorno (buf, MUTT_YES);
              }
            if (r == MUTT_YES)
              {
                if (crypt_is_numerical_keyid (crypt_hook_val))
                  {
                    keyID = crypt_hook_val;
                    if (strncmp (keyID, "0x", 2) == 0)
                      keyID += 2;
