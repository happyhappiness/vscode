static const char *
get_ucpname(int property)
{
int i;
for (i = sizeof(utt)/sizeof(ucp_type_table); i >= 0; i--)
  {
  if (property == utt[i].value) break;
  }
return (i >= 0)? utt[i].name : "??";
}