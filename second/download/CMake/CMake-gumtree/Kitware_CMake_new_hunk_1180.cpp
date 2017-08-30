    tmp = *i;

    doEscape(tmp, "\\", "/");

    doEscape(tmp, " ", "\\ ");

    fprintf(out, "%s \\\n", tmp.c_str());

    //printf("include: %s \n", tmp.c_str());

  }

