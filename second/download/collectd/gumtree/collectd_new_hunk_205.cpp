  {
    if (strncasecmp (fields[i], "message=", strlen ("message=")) == 0)
    {
      status = parse_message (&n, fields + i, fields_num - i);
      if (status != 0)
      {
	print_to_socket (fh, "-1 Error parsing the message. Have you hit the "
	    "limit of %u bytes?\n", (unsigned int) sizeof (n.message));
      }
      break;
    }
    else
    {
      status = parse_option (&n, fields[i]);
      if (status != 0)
      {
	print_to_socket (fh, "-1 Error parsing option `%s'\n", fields[i]);
	break;
      }
    }
  } /* for (i) */

  /* Check for required fields and complain if anything is missing. */
  if ((status == 0) && (n.severity == 0))
  {
    print_to_socket (fh, "-1 Option `severity' missing.\n");
    status = -1;
  }
  if ((status == 0) && (n.time == 0))
  {
    print_to_socket (fh, "-1 Option `time' missing.\n");
    status = -1;
  }
  if ((status == 0) && (strlen (n.message) == 0))
  {
    print_to_socket (fh, "-1 No message or message of length 0 given.\n");
    status = -1;
  }

  /* If status is still zero the notification is fine and we can finally
   * dispatch it. */
  if (status == 0)
  {
    plugin_dispatch_notification (&n);
    print_to_socket (fh, "0 Success\n");
  }

  return (0);
} /* int handle_putnotif */

/* vim: set shiftwidth=2 softtabstop=2 tabstop=8 : */
