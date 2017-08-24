r(p3 = (*p3 || p3 - str > 2)? "/": ", "; *p3; p3++) {
          if(l < n)
            buf[l] = *p3;
          l++;
        }