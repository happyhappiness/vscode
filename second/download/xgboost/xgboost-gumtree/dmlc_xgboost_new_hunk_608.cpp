    FILE *fo = utils::FopenCheck(CHAR(asChar(fname)), "w");
    for (size_t i = 0; i < olen; ++i) {
      fprintf(fo, "booster[%lu]:\n", i);
      fprintf(fo, "%s", res[i]);
    }
    fclose(fo);
  }
