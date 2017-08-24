{
    // Try to find the program.
    std::string result = SystemTools::FindProgram(*it, path, noSystemPath);
    if (!result.empty()) {
      return result;
    }
  }