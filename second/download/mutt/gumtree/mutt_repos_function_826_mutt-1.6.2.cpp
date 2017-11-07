static int copy_delete_attach (BODY *b, FILE *fpin, FILE *fpout, char *date)
{
  BODY *part;

  for (part = b->parts ; part ; part = part->next)
  {
    if (part->deleted || part->parts)
    {
      /* Copy till start of this part */
      if (mutt_copy_bytes (fpin, fpout, part->hdr_offset - ftello (fpin)))
	return -1;

      if (part->deleted)
      {
	fprintf (fpout,
		 "Content-Type: message/external-body; access-type=x-mutt-deleted;\n"
		 "\texpiration=%s; length=" OFF_T_FMT "\n"
		 "\n", date + 5, part->length);
	if (ferror (fpout))
	  return -1;

	/* Copy the original mime headers */
	if (mutt_copy_bytes (fpin, fpout, part->offset - ftello (fpin)))
	  return -1;

	/* Skip the deleted body */
	fseeko (fpin, part->offset + part->length, SEEK_SET);
      }
      else
      {
	if (copy_delete_attach (part, fpin, fpout, date))
	  return -1;
      }
    }
  }

  /* Copy the last parts */
  if (mutt_copy_bytes (fpin, fpout, b->offset + b->length - ftello (fpin)))
    return -1;

  return 0;
}