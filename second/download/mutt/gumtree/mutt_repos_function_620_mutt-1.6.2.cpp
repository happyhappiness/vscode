int mutt_addr_is_user (ADDRESS *addr)
{
  const char *fqdn;

  /* NULL address is assumed to be the user. */
  if (!addr)
  {
    dprint (5, (debugfile, "mutt_addr_is_user: yes, NULL address\n"));
    return 1;
  }
  if (!addr->mailbox)
  {
    dprint (5, (debugfile, "mutt_addr_is_user: no, no mailbox\n"));
    return 0;
  }

  if (ascii_strcasecmp (addr->mailbox, Username) == 0)
  {
    dprint (5, (debugfile, "mutt_addr_is_user: yes, %s = %s\n", addr->mailbox, Username));
    return 1;
  }
  if (string_is_address(addr->mailbox, Username, Hostname))
  {
    dprint (5, (debugfile, "mutt_addr_is_user: yes, %s = %s @ %s \n", addr->mailbox, Username, Hostname));
    return 1;
  }
  fqdn = mutt_fqdn (0);
  if (string_is_address(addr->mailbox, Username, fqdn))
  {
    dprint (5, (debugfile, "mutt_addr_is_user: yes, %s = %s @ %s \n", addr->mailbox, Username, NONULL(fqdn)));
    return 1;
  }
  fqdn = mutt_fqdn (1);
  if (string_is_address(addr->mailbox, Username, fqdn))
  {
    dprint (5, (debugfile, "mutt_addr_is_user: yes, %s = %s @ %s \n", addr->mailbox, Username, NONULL(fqdn)));
    return 1;
  }

  if (From && !ascii_strcasecmp (From->mailbox, addr->mailbox))
  {
    dprint (5, (debugfile, "mutt_addr_is_user: yes, %s = %s\n", addr->mailbox, From->mailbox));
    return 1;
  }

  if (mutt_match_rx_list (addr->mailbox, Alternates))
  {
    dprint (5, (debugfile, "mutt_addr_is_user: yes, %s matched by alternates.\n", addr->mailbox));
    if (mutt_match_rx_list (addr->mailbox, UnAlternates))
      dprint (5, (debugfile, "mutt_addr_is_user: but, %s matched by unalternates.\n", addr->mailbox));
    else
      return 1;
  }
  
  dprint (5, (debugfile, "mutt_addr_is_user: no, all failed.\n"));
  return 0;
}