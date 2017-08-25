int cmcompress_compress_start(struct cmcompress_stream* cdata)
{
#ifndef COMPATIBLE
  if (cdata->nomagic == 0)
    {
    char headLast = (char)(cdata->maxbits | cdata->block_compress);
    cdata->output_stream(cdata, (const char*)magic_header, 2);
    cdata->output_stream(cdata, &headLast, 1);
    if(ferror(stdout))
      {
      printf("Error...\n");
      }
    }
#endif /* COMPATIBLE */

  cdata->offset = 0;
  cdata->bytes_out = 3;    /* includes 3-byte header mojo */
  cdata->out_count = 0;
  cdata->clear_flg = 0;
  cdata->ratio = 0;
  cdata->in_count = 1;
  cdata->checkpoint = CHECK_GAP;
  cdata->maxcode = MAXCODE(cdata->n_bits = INIT_BITS);
  cdata->free_ent = ((cdata->block_compress) ? FIRST : 256 );

  cdata->first_pass = 1;

  cdata->hshift = 0;
  for ( cdata->fcode = (long) cdata->hsize;  cdata->fcode < 65536L; cdata->fcode *= 2L )
    {
    cdata->hshift++;
    }
  cdata->hshift = 8 - cdata->hshift;    /* set hash code range bound */

  cdata->hsize_reg = cdata->hsize;
  cl_hash(cdata, (count_int) cdata->hsize_reg);    /* clear hash table */

  return 1;
}