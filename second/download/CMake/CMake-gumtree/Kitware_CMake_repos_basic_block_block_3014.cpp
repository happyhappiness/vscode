{

         /*-- copy 1 --*/
         if (i > hi) break;
         v = ptr[i];
         j = i;
         while ( mainGtU ( 
                    ptr[j-h]+d, v+d, block, quadrant, nblock, budget 
                 ) ) {
            ptr[j] = ptr[j-h];
            j = j - h;
            if (j <= (lo + h - 1)) break;
         }
         ptr[j] = v;
         i++;

         /*-- copy 2 --*/
         if (i > hi) break;
         v = ptr[i];
         j = i;
         while ( mainGtU ( 
                    ptr[j-h]+d, v+d, block, quadrant, nblock, budget 
                 ) ) {
            ptr[j] = ptr[j-h];
            j = j - h;
            if (j <= (lo + h - 1)) break;
         }
         ptr[j] = v;
         i++;

         /*-- copy 3 --*/
         if (i > hi) break;
         v = ptr[i];
         j = i;
         while ( mainGtU ( 
                    ptr[j-h]+d, v+d, block, quadrant, nblock, budget 
                 ) ) {
            ptr[j] = ptr[j-h];
            j = j - h;
            if (j <= (lo + h - 1)) break;
         }
         ptr[j] = v;
         i++;

         if (*budget < 0) return;
      }