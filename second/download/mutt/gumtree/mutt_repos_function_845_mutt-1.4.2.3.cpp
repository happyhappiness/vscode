static const char *
parse_route_addr (const char *s,
		  char *comment, size_t *commentlen, size_t commentmax,
		  ADDRESS *addr)
{
  char token[STRING];
  size_t tokenlen = 0;

  SKIPWS (s);

  /* find the end of the route */
  if (*s == '@')
  {
    while (s && *s == '@')
    {
      if (tokenlen < sizeof (token) - 1)
	token[tokenlen++] = '@';
      s = parse_mailboxdomain (s + 1, ",.\\[](", token,
			       &tokenlen, sizeof (token) - 1,
			       comment, commentlen, commentmax);
    }
    if (!s || *s != ':')
    {
      RFC822Error = ERR_BAD_ROUTE;
      return NULL; /* invalid route */
    }

    if (tokenlen < sizeof (token) - 1)
      token[tokenlen++] = ':';
    s++;
  }

  if ((s = parse_address (s, token, &tokenlen, sizeof (token) - 1, comment, commentlen, commentmax, addr)) == NULL)
    return NULL;

  if (*s != '>' || !addr->mailbox)
  {
    RFC822Error = ERR_BAD_ROUTE_ADDR;
    return NULL;
  }

  s++;
  return s;
}