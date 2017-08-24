(int i = 0; i < args.argc(); i++) {
    char const* u8_arg = u8_argv[i];
    if (strcmp(argv[i], u8_arg) != 0) {
      std::cout << "argv[" << i << "] " << argv[i] << " != " << u8_arg
                << std::endl;
      status++;
    }
  }