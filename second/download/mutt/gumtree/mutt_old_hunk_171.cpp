	  return -1;
	case  2:	/* no */
	  FREE (directory);		/* __FREE_CHECKED__ */
	  return 1;
      }
    }
    else if ((rc = mutt_yesorno (_("File is a directory, save under it?"), M_YES)) != M_YES)
      return (rc == M_NO) ? 1 : -1;

    strfcpy (tmp, mutt_basename (NONULL (attname)), sizeof (tmp));
    if (mutt_get_field (_("File under directory: "), tmp, sizeof (tmp),
                                    M_FILE | M_CLEAR) != 0 || !tmp[0])
