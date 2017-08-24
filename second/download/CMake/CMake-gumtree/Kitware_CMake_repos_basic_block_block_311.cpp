{
          assert(argp != 0);
          return( 
                 Check_Field(typ->left ,field,argp->left ) ||
                 Check_Field(typ->right,field,argp->right) );
        }