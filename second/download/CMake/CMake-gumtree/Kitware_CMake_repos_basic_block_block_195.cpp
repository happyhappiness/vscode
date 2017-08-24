{
          assert(argp != 0);
          return(
            Check_Char(typ->left ,ch,argp->left ) ||
            Check_Char(typ->right,ch,argp->right) );
        }