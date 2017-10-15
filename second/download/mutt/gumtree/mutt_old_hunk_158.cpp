    }

  if (key->issuer_serial)
    {
      s = key->issuer_serial;
      if (s)
	fprintf (fp, _("Serial-No .: 0x%s\n"), s);
    }

  if (key->issuer_name)
    {
      s = key->issuer_name;
      if (s)
	{
	  fprintf (fp, _("Issued By .: "));
	  parse_and_print_user_id (fp, s);
	  putc ('\n', fp);
	}
    }

