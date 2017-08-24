{
  if (test_functions() == 1) {
    return 1;
  }
  std::cout
    << "this executable doesn't use cuda code, just call methods defined"
    << std::endl;
  std::cout << "in object files that have cuda code" << std::endl;
  return 0;
}