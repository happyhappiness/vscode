(strcmp(build_config_name, "release") != 0) {
    fprintf(stderr, "build_config_name is not \"release\"\n");
    return 1;
  }