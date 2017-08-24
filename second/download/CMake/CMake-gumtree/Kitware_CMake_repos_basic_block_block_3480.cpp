{ 
                  /* general case */
                  lno = nn / MTFL_SIZE;
                  off = nn % MTFL_SIZE;
                  pp = s->mtfbase[lno] + off;
                  uc = s->mtfa[pp];
                  while (pp > s->mtfbase[lno]) { 
                     s->mtfa[pp] = s->mtfa[pp-1]; pp--; 
                  };
                  s->mtfbase[lno]++;
                  while (lno > 0) {
                     s->mtfbase[lno]--;
                     s->mtfa[s->mtfbase[lno]] 
                        = s->mtfa[s->mtfbase[lno-1] + MTFL_SIZE - 1];
                     lno--;
                  }
                  s->mtfbase[0]--;
                  s->mtfa[s->mtfbase[0]] = uc;
                  if (s->mtfbase[0] == 0) {
                     kk = MTFA_SIZE-1;
                     for (ii = 256 / MTFL_SIZE-1; ii >= 0; ii--) {
                        for (jj = MTFL_SIZE-1; jj >= 0; jj--) {
                           s->mtfa[kk] = s->mtfa[s->mtfbase[ii] + jj];
                           kk--;
                        }
                        s->mtfbase[ii] = kk + 1;
                     }
                  }
               }