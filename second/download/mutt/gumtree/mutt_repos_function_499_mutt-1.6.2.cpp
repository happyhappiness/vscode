static int count_body_parts_check(LIST **checklist, BODY *b, int dflt)
{
  LIST *type;
  ATTACH_MATCH *a;

  /* If list is null, use default behavior. */
  if (! *checklist)
  {
    /*return dflt;*/
    return 0;
  }

  for (type = *checklist; type; type = type->next)
  {
    a = (ATTACH_MATCH *)type->data;
    dprint(5, (debugfile, "cbpc: %s %d/%s ?? %s/%s [%d]... ",
		dflt ? "[OK]   " : "[EXCL] ",
		b->type, b->subtype, a->major, a->minor, a->major_int));
    if ((a->major_int == TYPEANY || a->major_int == b->type) &&
	!regexec(&a->minor_rx, b->subtype, 0, NULL, 0))
    {
      dprint(5, (debugfile, "yes\n"));
      return 1;
    }
    else
    {
      dprint(5, (debugfile, "no\n"));
    }
  }

  return 0;
}