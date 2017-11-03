static void _attachments_clean (void)
{
  int i;
  if (Context && Context->msgcount) 
  {
    for (i = 0; i < Context->msgcount; i++)
      Context->hdrs[i]->attach_valid = 0;
  }
}