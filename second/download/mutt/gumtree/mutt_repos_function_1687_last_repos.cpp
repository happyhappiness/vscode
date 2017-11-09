static int pgp_parse_pgp3_sig (unsigned char *buff, size_t l,
                               pgp_key_t p, pgp_sig_t *s)
{
  unsigned char sigtype;
  unsigned char skt;
  time_t sig_gen_time = -1;
  long validity = -1;
  long key_validity = -1;
  unsigned long signerid1 = 0;
  unsigned long signerid2 = 0;
  size_t ml;
  size_t j;
  int i;
  short ii;
  short have_critical_spks = 0;

  if (l < 7)
    return -1;

  j = 2;

  sigtype = buff[j++];
  j += 2; /* pkalg, hashalg */

  for (ii = 0; ii < 2; ii++)
  {
    size_t skl;
    size_t nextone;

    ml = (buff[j] << 8) + buff[j + 1];
    j += 2;

    if (j + ml > l)
      break;

    nextone = j;
    while (ml)
    {
      j = nextone;
      skl = buff[j++];
      if (!--ml)
	break;

      if (skl >= 192)
      {
	skl = (skl - 192) * 256 + buff[j++] + 192;
	if (!--ml)
	  break;
      }

      if ((int) ml - (int) skl < 0)
	break;
      ml -= skl;

      nextone = j + skl;
      skt = buff[j++];

      switch (skt & 0x7f)
      {
	case 2:			/* creation time */
	{
	  if (skl < 4)
	    break;
	  sig_gen_time = 0;
	  for (i = 0; i < 4; i++)
	    sig_gen_time = (sig_gen_time << 8) + buff[j++];

	  break;
	}
	case 3:			/* expiration time */
	{
	  if (skl < 4)
	    break;
	  validity = 0;
	  for (i = 0; i < 4; i++)
	    validity = (validity << 8) + buff[j++];
	  break;
	}
	case 9:			/* key expiration time */
	{
	  if (skl < 4)
	    break;
	  key_validity = 0;
	  for (i = 0; i < 4; i++)
	    key_validity = (key_validity << 8) + buff[j++];
	  break;
	}
	case 16:			/* issuer key ID */
	{
	  if (skl < 8)
	    break;
	  signerid2 = signerid1 = 0;
	  for (i = 0; i < 4; i++)
	    signerid1 = (signerid1 << 8) + buff[j++];
	  for (i = 0; i < 4; i++)
	    signerid2 = (signerid2 << 8) + buff[j++];
	  
	  break;
	}
	case 10:			/* CMR key */
	break;
	case 4:				/* exportable */
	case 5:				/* trust */
	case 6:				/* regexp */
	case 7:				/* revocable */
	case 11:			/* Pref. symm. alg. */
	case 12:			/* revocation key */
	case 20:			/* notation data */
	case 21:			/* pref. hash */
	case 22:			/* pref. comp.alg. */
	case 23:			/* key server prefs. */
	case 24:			/* pref. key server */
	default:
	{
	  if (skt & 0x80)
	    have_critical_spks = 1;
	}
      }
    }
    j = nextone;
  }

  if (sigtype == 0x20 || sigtype == 0x28)
    p->flags |= KEYFLAG_REVOKED;
  if (key_validity != -1 && time (NULL) > p->gen_time + key_validity)
    p->flags |= KEYFLAG_EXPIRED;
  if (have_critical_spks)
    p->flags |= KEYFLAG_CRITICAL;

  if (s)
  {
    s->sigtype = sigtype;
    s->sid1    = signerid1;
    s->sid2    = signerid2;
  }

  
  return 0;

}