int handle_putnotif (FILE *fh, char **fields, int fields_num)
{
  notification_t n;
  int status;
  int i;

  /* Required fields: `PUTNOTIF', severity, time, message */
  if (fields_num < 4)
  {
    DEBUG ("cmd putnotif: Wrong number of fields: %i", fields_num);
    fprintf (fh, "-1 Wrong number of fields: Got %i, expected at least 4.\n",
	fields_num);
    fflush (fh);
    return (-1);
  }

  memset (&n, '\0', sizeof (n));

  status = 0;
  for (i = 1; i < fields_num; i++)
  {
    if (strncasecmp (fields[i], "message=", strlen ("message=")) == 0)
    {
      status = parse_message (&n, fields + i, fields_num - i);
      if (status != 0)
      {
	fprintf (fh, "-1 Error parsing the message. Have you hit the "
	    "limit of %u bytes?\n", (unsigned int) sizeof (n.message));
      }
      break;
    }
    else
    {
      status = parse_option (&n, fields[i]);
      if (status != 0)
      {
	fprintf (fh, "-1 Error parsing option `%s'\n", fields[i]);
	break;
      }
    }
  } /* for (i) */

  /* Check for required fields and complain if anything is missing. */
  if ((status == 0) && (n.severity == 0))
  {
    fprintf (fh, "-1 Option `severity' missing.\n");
    status = -1;
  }
  if ((status == 0) && (n.time == 0))
  {
    fprintf (fh, "-1 Option `time' missing.\n");
    status = -1;
  }
  if ((status == 0) && (strlen (n.message) == 0))
  {
    fprintf (fh, "-1 No message or message of length 0 given.\n");
    status = -1;
  }

  /* If status is still zero the notification is fine and we can finally
   * dispatch it. */
  if (status == 0)
  {
    plugin_dispatch_notification (&n);
    fprintf (fh, "0 Success\n");
  }
  fflush (fh);

  return (0);
}