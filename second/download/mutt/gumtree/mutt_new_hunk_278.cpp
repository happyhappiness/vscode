          if (sep) fputs (sep, fpout);
        }
      }
      safe_fclose (&fpout);
      if (mutt_wait_filter (thepid) != 0)
	rc = 1;
      unset_option (OPTKEEPQUIET);
    }
  }

  if (rc || option (OPTWAITKEY))
    mutt_any_key_to_continue (NULL);
  return rc;
