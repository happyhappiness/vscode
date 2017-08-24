{
         VPrintf2 ( "      pass %d: size is %d, grp uses are ", 
                   iter+1, totc/8 );
         for (t = 0; t < nGroups; t++)
            VPrintf1 ( "%d ", fave[t] );
         VPrintf0 ( "\n" );
      }