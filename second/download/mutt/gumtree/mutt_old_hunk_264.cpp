	  if (non_pka_notations)
	  {
	    char buf[SHORT_STRING];
	    snprintf (buf, sizeof (buf),
		      _("*** Begin Notation (signature by: %s) ***\n"),
		      signature->fpr);
	    state_attach_puts (buf, s);
	    for (notation = signature->notations; notation;
                 notation = notation->next)
	    {
	      if (is_pka_notation (notation))
		continue;

	      if (notation->name)
	      {
		state_attach_puts (notation->name, s);
		state_attach_puts ("=", s);
	      }
	      if (notation->value)
	      {
		state_attach_puts (notation->value, s);
		if (!(*notation->value
                      && (notation->value[strlen (notation->value)-1]=='\n')))
		  state_attach_puts ("\n", s);
	      }
	    }
	    state_attach_puts (_("*** End Notation ***\n"), s);
	  }
	}
      }
    }

  gpgme_release (ctx);
