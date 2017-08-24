{
  TypeArgument *res = (TypeArgument *)0; 
  TypeArgument *p;

  if (typ && (typ->status & _HAS_ARGS))
    {
      assert(err && ap);
      if (typ->status & _LINKED_TYPE)
	{
	  p = (TypeArgument *)malloc(sizeof(TypeArgument));
	  if (p) 
	    {
	      p->left  = _nc_Make_Argument(typ->left ,ap,err);
	      p->right = _nc_Make_Argument(typ->right,ap,err);
	      return p;
	    }
	  else
	    *err += 1;
      } else 
	{
	  assert(typ->makearg != 0);
	  if ( !(res=(TypeArgument *)typ->makearg(ap)) ) 
	    *err += 1;
	}
    }
  return res;
}