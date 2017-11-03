static void mutt_free_opt (struct option_t* p)
{
  REGEXP* pp;

  switch (p->type & DT_MASK)
  {
  case DT_ADDR:
    rfc822_free_address ((ADDRESS**)p->data);
    break;
  case DT_RX:
    pp = (REGEXP*)p->data;
    FREE (&pp->pattern);
    if (pp->rx)
    {
      regfree (pp->rx);
      FREE (&pp->rx);
    }
    break;
  case DT_PATH:
  case DT_STR:
    FREE ((char**)p->data);		/* __FREE_CHECKED__ */
    break;
  }
}