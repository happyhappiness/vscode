    //doEscape(tmp, "(", "\\("); // TODO ninja can't read ( and )

    //doEscape(tmp, ")", "\\)");

    fprintf(out, "%s \\\n", tmp.c_str());

    //printf("include: %s \n", tmp.c_str());

  }



  fprintf(out, "\n");

