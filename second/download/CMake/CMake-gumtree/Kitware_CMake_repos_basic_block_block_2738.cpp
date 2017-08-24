{
    if (argv[1] != std::string("--forceFail")) {
      throw "Unexpected argument";
    }
    shouldFail = true;
  }