        fprintf (*fp, "%s %5.5s %d/%8s %s\n", more ? "sub" : "pub",
                 gpgme_pubkey_algo_name (subkey->pubkey_algo), subkey->length,
                 shortid, date);      
      subkey = subkey->next;
      more = 1;
    }
    gpgme_key_release (key);
  }
  if (gpg_err_code (err) != GPG_ERR_EOF)
  {
    dprint (1, (debugfile, "Error listing keys\n"));
    goto err_fp;
  }
