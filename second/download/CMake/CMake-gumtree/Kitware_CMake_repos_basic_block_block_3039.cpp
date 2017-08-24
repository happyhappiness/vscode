{
            if (unLo > unHi) break;
            n = ((Int32)block[ptr[unLo]+d]) - med;
            if (n == 0) { 
               mswap(ptr[unLo], ptr[ltLo]); 
               ltLo++; unLo++; continue; 
            };
            if (n >  0) break;
            unLo++;
         }