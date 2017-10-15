	rv = (pgp_check_traditional_one_body (fp, b, tagged_only) || rv);
    }
  }
  return rv;
}

void pgp_gpgme_invoke_import (const char *fname)
{
  gpgme_data_t keydata;
  gpgme_error_t err;
  FILE* in;
  FILE* out;

  if (!(in = safe_fopen (fname, "r")))
    return;
  /* Note that the stream, "in", needs to be kept open while the keydata
   * is used.
   */
  if ((err = gpgme_data_new_from_stream (&keydata, in)) != GPG_ERR_NO_ERROR)
  {
    safe_fclose (&in);
    mutt_error (_("error allocating data object: %s\n"), gpgme_strerror (err));
    mutt_sleep (1);
    return;
  }

  if (pgp_gpgme_extract_keys (keydata, &out, 0))
  {
    mutt_error (_("Error extracting key data!\n"));
    mutt_sleep (1);
  }
  gpgme_data_release (keydata);
  safe_fclose (&in);
  safe_fclose (&out);
}


/* 
 * Implementation of `application_handler'.
 */
