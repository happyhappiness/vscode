(strcmp(build_config_name, "relwithdebinfo") != 0) {
    fprintf(stderr, "build_config_name is not \"relwithdebinfo\"\n");
    return 1;
  }