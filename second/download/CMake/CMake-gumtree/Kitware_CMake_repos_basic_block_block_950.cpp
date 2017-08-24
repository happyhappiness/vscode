{
  // Call the callback
  if (cs->Callback) {
    if (!cs->Callback(cs->Argument, value, cs->CallData)) {
      this->Internals->LastArgument--;
      return 0;
    }
  }
  CommandLineArguments_DEBUG("Set argument: " << cs->Argument << " to "
                                              << value);
  if (cs->Variable) {
    std::string var = "1";
    if (value) {
      var = value;
    }
    switch (cs->VariableType) {
      case CommandLineArguments::INT_TYPE:
        this->PopulateVariable(static_cast<int*>(cs->Variable), var);
        break;
      case CommandLineArguments::DOUBLE_TYPE:
        this->PopulateVariable(static_cast<double*>(cs->Variable), var);
        break;
      case CommandLineArguments::STRING_TYPE:
        this->PopulateVariable(static_cast<char**>(cs->Variable), var);
        break;
      case CommandLineArguments::STL_STRING_TYPE:
        this->PopulateVariable(static_cast<std::string*>(cs->Variable), var);
        break;
      case CommandLineArguments::BOOL_TYPE:
        this->PopulateVariable(static_cast<bool*>(cs->Variable), var);
        break;
      case CommandLineArguments::VECTOR_BOOL_TYPE:
        this->PopulateVariable(static_cast<std::vector<bool>*>(cs->Variable),
                               var);
        break;
      case CommandLineArguments::VECTOR_INT_TYPE:
        this->PopulateVariable(static_cast<std::vector<int>*>(cs->Variable),
                               var);
        break;
      case CommandLineArguments::VECTOR_DOUBLE_TYPE:
        this->PopulateVariable(static_cast<std::vector<double>*>(cs->Variable),
                               var);
        break;
      case CommandLineArguments::VECTOR_STRING_TYPE:
        this->PopulateVariable(static_cast<std::vector<char*>*>(cs->Variable),
                               var);
        break;
      case CommandLineArguments::VECTOR_STL_STRING_TYPE:
        this->PopulateVariable(
          static_cast<std::vector<std::string>*>(cs->Variable), var);
        break;
      default:
        std::cerr << "Got unknown variable type: \"" << cs->VariableType
                  << "\"" << std::endl;
        this->Internals->LastArgument--;
        return 0;
    }
  }
  return 1;
}