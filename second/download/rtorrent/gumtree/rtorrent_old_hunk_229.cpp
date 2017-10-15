    int status;

    if (waitpid(childPid, &status, 0) != childPid)
      throw torrent::internal_error("ExecFile::execute(...) waitpid failed.");

    // Check return value?

    return status;
  }
}

torrent::Object
ExecFile::execute_object(const torrent::Object& rawArgs) {
  char*  argsBuffer[128];
  char** argsCurrent = argsBuffer;

  // Size of strings are less than 24.
  char   valueBuffer[3072];
  char*  valueCurrent = valueBuffer;

  const torrent::Object::list_type& args = rawArgs.as_list();

  if (args.empty())
    throw torrent::input_error("Too few arguments.");

  for (torrent::Object::list_type::const_iterator itr = args.begin(), last = args.end(); itr != last; itr++, argsCurrent++) {
    if (argsCurrent == argsBuffer + 128 - 1)
      throw torrent::input_error("Too many arguments.");

    switch (itr->type()) {
    case torrent::Object::TYPE_STRING:
      *argsCurrent = const_cast<char*>(itr->as_string().c_str());
      break;

    case torrent::Object::TYPE_VALUE:
      *argsCurrent = valueCurrent;

      valueCurrent += std::max(snprintf(valueCurrent, valueBuffer + 3072 - valueCurrent, "%lli", itr->as_value()), 0);
      break;

    default:
      throw torrent::input_error("Invalid type.");
    }
  }

  *argsCurrent = NULL;

  int status = execute(argsBuffer[0], argsBuffer);

  if (status != 0)
    throw torrent::input_error("ExecFile::execute_object(...) status != 0.");

  return torrent::Object();
}

}
