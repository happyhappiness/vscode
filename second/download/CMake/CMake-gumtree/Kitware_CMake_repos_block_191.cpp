{
    fprintf(stderr,
            "Error from reader: %s",
            reader.getFormattedErrorMessages().c_str());

    JSON_FAIL_MESSAGE("reader error");
  }