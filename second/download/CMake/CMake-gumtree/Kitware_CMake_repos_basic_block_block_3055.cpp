{
            k = ptr[j]-1; if (k < 0) k += nblock;
            c1 = block[k];
            if (!bigDone[c1])
               ptr[ copyStart[c1]++ ] = k;
         }