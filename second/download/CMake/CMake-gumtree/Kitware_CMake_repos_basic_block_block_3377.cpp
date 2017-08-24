{
            zPend--;
            while (True) {
               if (zPend & 1) {
                  mtfv[wr] = BZ_RUNB; wr++; 
                  s->mtfFreq[BZ_RUNB]++; 
               } else {
                  mtfv[wr] = BZ_RUNA; wr++; 
                  s->mtfFreq[BZ_RUNA]++; 
               }
               if (zPend < 2) break;
               zPend = (zPend - 2) / 2;
            };
            zPend = 0;
         }