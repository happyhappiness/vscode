    tmp = *i;

    doEscape(tmp, "\\", "/");

    doEscape(tmp, " ", "\\ ");

    //doEscape(tmp, "(", "("); // TODO ninja cant read ( and )

    //doEscape(tmp, ")", ")");

    fprintf(out, "%s \\\n", tmp.c_str());

  }



