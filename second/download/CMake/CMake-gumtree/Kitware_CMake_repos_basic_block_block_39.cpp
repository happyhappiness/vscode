{
  TypeArgument *res = (TypeArgument *)0;
  TypeArgument *p;

  if ( typ && (typ->status & _HAS_ARGS) )
    {
      assert(err && argp);
      if (typ->status & _LINKED_TYPE)
	{
	  p = (TypeArgument *)malloc(sizeof(TypeArgument));
	  if (p)
	    {
	      p->left  = _nc_Copy_Argument(typ,argp->left ,err);
	      p->right = _nc_Copy_Argument(typ,argp->right,err);
	      return p;
	    }
	  *err += 1;
      } 
      else 
	{
	  if (typ->copyarg)
	    {
	      if (!(res = (TypeArgument *)(typ->copyarg((const void *)argp)))) 
		*err += 1;
	    }
	  else
	    res = (TypeArgument *)argp;
	}
    }
  return res;
}