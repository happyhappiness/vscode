(ii = 256 / MTFL_SIZE-1; ii >= 0; ii--) {
                        for (jj = MTFL_SIZE-1; jj >= 0; jj--) {
                           s->mtfa[kk] = s->mtfa[s->mtfbase[ii] + jj];
                           kk--;
                        }
                        s->mtfbase[ii] = kk + 1;
                     }