{
  std::cout << "Got argument: \"" << arg << "\" value: \""
            << (value ? value : "(null)") << "\"" << std::endl;
  if (call_data != random_ptr) {
    std::cerr << "Problem processing call_data" << std::endl;
    return 0;
  }
  return 1;
}