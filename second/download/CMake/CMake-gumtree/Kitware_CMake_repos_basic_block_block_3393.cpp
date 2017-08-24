(i = 0; i < alphaSize; i++) {
         while (curr < s->len[t][i]) { bsW(s,2,2); curr++; /* 10 */ };
         while (curr > s->len[t][i]) { bsW(s,2,3); curr--; /* 11 */ };
         bsW ( s, 1, 0 );
      }