static void mix_free_type2_list (REMAILER ***ttlp)
{
  int i;
  REMAILER **type2_list = *ttlp;
  
  for (i = 0; type2_list[i]; i++)
    mix_free_remailer (&type2_list[i]);
  
  safe_free ((void **) type2_list);
}