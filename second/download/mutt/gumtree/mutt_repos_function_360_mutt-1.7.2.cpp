int mutt_parse_exec (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  int ops[128]; 
  int nops = 0;
  const struct binding_t *bindings = NULL;
  char *function;

  if (!MoreArgs (s))
  {
    strfcpy (err->data, _("exec: no arguments"), err->dsize);
    return (-1);
  }

  do
  {
    mutt_extract_token (buf, s, 0);
    function = buf->data;

    if ((bindings = km_get_table (CurrentMenu)) == NULL 
	&& CurrentMenu != MENU_PAGER)
      bindings = OpGeneric;

    ops[nops] = get_op (bindings, function, mutt_strlen(function));
    if (ops[nops] == OP_NULL && CurrentMenu != MENU_PAGER)
      ops[nops] = get_op (OpGeneric, function, mutt_strlen(function));

    if (ops[nops] == OP_NULL)
    {
      mutt_flushinp ();
      mutt_error (_("%s: no such function"), function);
      return (-1);
    }
    nops++;
  }
  while(MoreArgs(s) && nops < sizeof(ops)/sizeof(ops[0]));

  while(nops)
    mutt_push_macro_event (0, ops[--nops]);

  return 0;
}