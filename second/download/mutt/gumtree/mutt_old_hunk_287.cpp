              tm = localtime (&tt);
#ifdef HAVE_LANGINFO_D_T_FMT
              strftime (shortbuf, sizeof shortbuf, nl_langinfo (D_T_FMT), tm);
#else
              strftime (shortbuf, sizeof shortbuf, "%c", tm);
#endif
              /* L10N: DOTFILL */
              fprintf (fp, _("Valid From : %s\n"), shortbuf);
            }

	  if (subkey->expires > 0)
	    {
	      tt = subkey->expires;

              tm = localtime (&tt);
#ifdef HAVE_LANGINFO_D_T_FMT
              strftime (shortbuf, sizeof shortbuf, nl_langinfo (D_T_FMT), tm);
#else
              strftime (shortbuf, sizeof shortbuf, "%c", tm);
#endif
              /* L10N: DOTFILL */
              fprintf (fp, _("Valid To ..: %s\n"), shortbuf);
            }

	  if (subkey)
	    s = gpgme_pubkey_algo_name (subkey->pubkey_algo);
	  else
            s = "?";

	  if (subkey)
	    aval = subkey->length;
	  else
	    aval = 0;

          /* L10N: DOTFILL */
          fprintf (fp, _("Key Type ..: %s, %lu bit %s\n"), "PGP", aval, s);

          /* L10N: DOTFILL */
          fprintf (fp, _("Key Usage .: "));
          delim = "";

	  if (subkey->can_encrypt)
            {
              fprintf (fp, "%s%s", delim, _("encryption"));
              delim = _(", ");
