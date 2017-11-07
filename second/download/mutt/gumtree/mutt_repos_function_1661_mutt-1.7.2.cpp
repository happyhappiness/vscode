static void _alternates_clean (void)
{
  int i;
  if (Context && Context->msgcount) 
  {
    for (i = 0; i < Context->msgcount; i++)
      Context->hdrs[i]->recip_valid = 0;
  }
}