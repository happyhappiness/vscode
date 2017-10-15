	  break;

	case 'e':
	case 'v':
	  if (be_barf_file (path, buf, buflen) == 0)
	  {
	    be_free_memory (buf, buflen);
	    buf = NULL;
	    bufmax = buflen = 0;

	    if (option (OPTEDITHDRS))
	      mutt_edit_headers (NONULL(Visual), path, msg, NULL, 0);
	    else
	      mutt_edit_file (NONULL(Visual), path);

	    buf = be_snarf_file (path, buf, &bufmax, &buflen, 0);

	    addstr (_("(continue)\n"));
