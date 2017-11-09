static unsigned int http2_conncheck(struct connectdata *check,
                                    unsigned int checks_to_perform)
{
  unsigned int ret_val = CONNRESULT_NONE;

  if(checks_to_perform & CONNCHECK_ISDEAD) {
    if(http2_connisdead(check))
      ret_val |= CONNRESULT_DEAD;
  }

  return ret_val;
}