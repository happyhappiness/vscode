{
      assert(argp != 0);
      _nc_Free_Argument(typ->left ,argp->left );
      _nc_Free_Argument(typ->right,argp->right);
      free(argp);
    }