    else { /* format item */
      char form[MAX_FORMAT];  /* to store the format (`%...') */
      char buff[MAX_ITEM];  /* to store the formatted item */
      arg++;
      strfrmt = scanformat(L, strfrmt, form);
      switch (*strfrmt++) {
        case 'c': {
