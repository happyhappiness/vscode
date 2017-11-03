static void mutt_set_default (struct option_t *p)
{
  switch (p->type & DT_MASK)
  {
    case DT_STR:
      if (!p->init && *((char **) p->data))
        p->init = (unsigned long) safe_strdup (* ((char **) p->data));
      break;
    case DT_PATH:
      if (!p->init && *((char **) p->data))
      {
	char *cp = safe_strdup (*((char **) p->data));
	/* mutt_pretty_mailbox (cp); */
        p->init = (unsigned long) cp;
      }
      break;
    case DT_ADDR:
      if (!p->init && *((ADDRESS **) p->data))
      {
	char tmp[HUGE_STRING];
	*tmp = '\0';
	rfc822_write_address (tmp, sizeof (tmp), *((ADDRESS **) p->data), 0);
	p->init = (unsigned long) safe_strdup (tmp);
      }
      break;
    case DT_RX:
    {
      REGEXP *pp = (REGEXP *) p->data;
      if (!p->init && pp->pattern)
	p->init = (unsigned long) safe_strdup (pp->pattern);
      break;
    }
  }
}