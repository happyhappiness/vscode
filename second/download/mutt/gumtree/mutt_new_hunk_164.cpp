	    bufmax = buflen = 0;

	    if (option (OPTEDITHDRS))
	    {
	      mutt_env_to_local (msg->env);
	      mutt_edit_headers (NONULL(Visual), path, msg, NULL, 0);
	      if (mutt_env_to_intl (msg->env, &tag, &err))
		printw (_("Bad IDN in %s: '%s'\n"), tag, err);
	    }
	    else
	      mutt_edit_file (NONULL(Visual), path);

	    buf = be_snarf_file (path, buf, &bufmax, &buflen, 0);
