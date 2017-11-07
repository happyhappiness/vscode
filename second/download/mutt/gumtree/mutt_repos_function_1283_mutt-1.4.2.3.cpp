static void cmd_parse_capabilities (IMAP_DATA* idata, char* s)
{
  int x;

  dprint (2, (debugfile, "Handling CAPABILITY\n"));

  s = imap_next_word (s);
  FREE(&idata->capstr);
  idata->capstr = safe_strdup (s);

  memset (idata->capabilities, 0, sizeof (idata->capabilities));

  while (*s)
  {
    for (x = 0; x < CAPMAX; x++)
      if (imap_wordcasecmp(Capabilities[x], s) == 0)
      {
	mutt_bit_set (idata->capabilities, x);
	break;
      }
    s = imap_next_word (s);
  }
}