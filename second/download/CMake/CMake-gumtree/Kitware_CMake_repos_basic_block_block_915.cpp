(kk = 0; kk < matches.size(); kk++) {
        if (matches[kk].size() > maxlen) {
          maxlen = matches[kk].size();
          maxidx = kk;
        }
      }