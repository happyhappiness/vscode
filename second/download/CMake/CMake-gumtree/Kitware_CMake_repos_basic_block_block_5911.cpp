f(sh) {
            if(!(IsPipeliningPossible(sh, check) & CURLPIPE_HTTP1))
              continue;
          }
          else if(rh) {
            if(!(IsPipeliningPossible(rh, check) & CURLPIPE_HTTP1))
              continue;
          }