{
  const enumARG *args = (const enumARG *)argp;
  int cnt       = args->count;
  char **kwds   = &args->kwds[cnt-1];
  bool ccase    = args->checkcase;
  unsigned char *bp = (unsigned char *)field_buffer(field,0);

  if (kwds) {
    while(cnt--)
      {
	if (Compare((unsigned char *)(*kwds--),bp,ccase)==EXACT) 
	  break;
      }
    
    if (cnt<=0)
      kwds  = &args->kwds[args->count-1];
    
    if ((cnt>=0) || (Compare((const unsigned char *)dummy,bp,ccase)==EXACT))
      {
	set_field_buffer(field,0,*kwds);
	return TRUE;
      }
  }
  return FALSE;
}