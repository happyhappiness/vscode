f(strcmp(needle->user, check->user) ||
           strcmp(needle->passwd, check->passwd)) {
          /* one of them was different */
          continue;
        }