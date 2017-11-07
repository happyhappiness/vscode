int mutt_addr_is_user (ADDRESS *addr)
{
  /* NULL address is assumed to be the user. */
  if (!addr)
    return 1;
  if (!addr->mailbox)
    return 0;

  if (ascii_strcasecmp (addr->mailbox, Username) == 0)
    return 1;
  if (string_is_address(addr->mailbox, Username, Hostname))
    return 1;
  if (string_is_address(addr->mailbox, Username, mutt_fqdn(0)))
    return 1;
  if (string_is_address(addr->mailbox, Username, mutt_fqdn(1)))
    return 1;

  if (From && !ascii_strcasecmp (From->mailbox, addr->mailbox))
    return 1;

  if (Alternates.pattern &&
      regexec (Alternates.rx, addr->mailbox, 0, NULL, 0) == 0)
    return 1;
  
  return 0;
}