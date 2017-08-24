(typ->status & _LINKED_TYPE)
        {
          assert(argp != 0);
          return(
            Check_Char(typ->left ,ch,argp->left ) ||
            Check_Char(typ->right,ch,argp->right) );
        } 
      else 
        {
          if (typ->ccheck)
            return typ->ccheck(ch,(void *)argp);
        }