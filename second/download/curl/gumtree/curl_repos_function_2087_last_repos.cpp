static int mime_open_file(curl_mimepart * part)
{
  /* Open a MIMEKIND_FILE part. */

  if(part->fp)
    return 0;
  part->fp = fopen_read(part->data, "rb");
  return part->fp? 0: -1;
}