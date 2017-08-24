(typ->status & _LINKED_TYPE)
    {
      assert(argp != 0);
      return(
             Next_Choice(typ->left ,field,argp->left) ||
             Next_Choice(typ->right,field,argp->right) );
    } 
  else
    {
      assert(typ->next != 0);
      return typ->next(field,(void *)argp);
    }