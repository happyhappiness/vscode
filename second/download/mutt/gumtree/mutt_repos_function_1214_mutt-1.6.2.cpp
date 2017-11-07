void mutt_stamp_attachment(BODY *a)
{
  a->stamp = time(NULL);
}