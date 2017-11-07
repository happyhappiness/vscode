static void cmd_parse_myrights (IMAP_DATA* idata, char* s)
{
  dprint (2, (debugfile, "Handling MYRIGHTS\n"));

  s = imap_next_word (s);
  s = imap_next_word (s);

  /* zero out current rights set */
  memset (idata->rights, 0, sizeof (idata->rights));

  while (*s && !isspace(*s))
  {
    switch (*s) 
    {
      case 'l':
	mutt_bit_set (idata->rights, IMAP_ACL_LOOKUP);
	break;
      case 'r':
	mutt_bit_set (idata->rights, IMAP_ACL_READ);
	break;
      case 's':
	mutt_bit_set (idata->rights, IMAP_ACL_SEEN);
	break;
      case 'w':
	mutt_bit_set (idata->rights, IMAP_ACL_WRITE);
	break;
      case 'i':
	mutt_bit_set (idata->rights, IMAP_ACL_INSERT);
	break;
      case 'p':
	mutt_bit_set (idata->rights, IMAP_ACL_POST);
	break;
      case 'c':
	mutt_bit_set (idata->rights, IMAP_ACL_CREATE);
	break;
      case 'd':
	mutt_bit_set (idata->rights, IMAP_ACL_DELETE);
	break;
      case 'a':
	mutt_bit_set (idata->rights, IMAP_ACL_ADMIN);
	break;
    }
    s++;
  }
}