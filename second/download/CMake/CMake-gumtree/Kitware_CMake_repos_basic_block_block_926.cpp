{
        skip = this->LineLength - maxlen;
        for (cc = skip - 1; cc > 0; cc--) {
          if (ptr[cc] == ' ' || ptr[cc] == '\t') {
            break;
          }
        }
        if (cc != 0) {
          skip = cc;
        }
      }