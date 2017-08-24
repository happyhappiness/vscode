f(bv.bv_len > 7 && !strncmp(bv.bv_val + bv.bv_len - 7, ";binary", 7))
        binary = 1;
      else
        binary = 0