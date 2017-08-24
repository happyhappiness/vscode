{
  std::cout << "Got unknown argument: \"" << argument << "\"" << std::endl;
  if (call_data != random_ptr) {
    std::cerr << "Problem processing call_data" << std::endl;
    return 0;
  }
  return 1;
}