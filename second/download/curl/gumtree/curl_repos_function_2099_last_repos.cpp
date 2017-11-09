static void cleanup_part_content(curl_mimepart *part)
{
  if(part->freefunc)
    part->freefunc(part->arg);

  part->readfunc = NULL;
  part->seekfunc = NULL;
  part->freefunc = NULL;
  part->arg = (void *) part;          /* Defaults to part itself. */
  part->data = NULL;
  part->fp = NULL;
  part->datasize = (curl_off_t) 0;    /* No size yet. */
  part->encoder = NULL;
  cleanup_encoder_state(&part->encstate);
  part->kind = MIMEKIND_NONE;
}