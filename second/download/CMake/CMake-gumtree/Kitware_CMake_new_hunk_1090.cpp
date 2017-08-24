  return 1;
}

static void cl_hash(struct cmcompress_stream* cdata, count_int hsize)    /* reset code table */
{
  register count_int *htab_p = cdata->htab+hsize;
