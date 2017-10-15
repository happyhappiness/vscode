	rv = (pgp_check_traditional_one_body (fp, b, tagged_only) || rv);
    }
  }
  return rv;
}

/* TODO: looks like this won't work and we'll have to fully parse the
 * message file. GPGME makes life hard yet again. */
void pgp_gpgme_invoke_import (const char *fname)
{
  gpgme_data_t keydata;
  gpgme_error_t err;
  FILE* in;
  FILE* out;
  long outlen;

  if (!(in = safe_fopen (fname, "r")))
    return;
  if ((err = gpgme_data_new_from_stream (&keydata, in)) != GPG_ERR_NO_ERROR)
  {
    dprint (1, (debugfile, "error converting key file into data object\n"));
    return;
  }
  safe_fclose (&in);

  if (!pgp_gpgme_extract_keys (keydata, &out, 0))
  {
    /* display import results */
    outlen = ftell (out);
    fseek (out, 0, SEEK_SET);
    mutt_copy_bytes (out, stdout, outlen);
    safe_fclose (&out);
  }
  else
    printf (_("Error extracting key data!\n"));
}


/* 
 * Implementation of `application_handler'.
 */
