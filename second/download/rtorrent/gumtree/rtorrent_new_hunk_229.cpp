    int status;

    if (waitpid(childPid, &status, 0) != childPid)
      throw torrent::internal_error("ExecFile::execute(...) waitpid failed.");

    // Check return value?
    if (m_logFd) {
      if (status == 0)
        write(m_logFd, "\n--- Success ---\n", sizeof("\n--- Success ---\n"));
      else
        write(m_logFd, "\n--- Error ---\n", sizeof("\n--- Error ---\n"));
    }

    return status;
  }
}

torrent::Object
ExecFile::execute_object(const torrent::Object& rawArgs, int flags) {
  char*  argsBuffer[max_args];
  char** argsCurrent = argsBuffer;

  // Size of value strings are less than 24.
  char   valueBuffer[buffer_size];
  char*  valueCurrent = valueBuffer;

  const torrent::Object::list_type& args = rawArgs.as_list();

  if (args.empty())
    throw torrent::input_error("Too few arguments.");

  for (torrent::Object::list_type::const_iterator itr = args.begin(), last = args.end(); itr != last; itr++, argsCurrent++) {
    if (argsCurrent == argsBuffer + max_args - 1)
      throw torrent::input_error("Too many arguments.");

    if (itr->is_string() && (!(flags & flag_expand_tilde) || *itr->as_string().c_str() != '~')) {
      *argsCurrent = const_cast<char*>(itr->as_string().c_str());

    } else {
      *argsCurrent = valueCurrent;
      valueCurrent = print_object(valueCurrent, valueBuffer + buffer_size, &*itr, flags) + 1;

      if (valueCurrent >= valueBuffer + buffer_size)
        throw torrent::input_error("Overflowed execute arg buffer.");
    }      
  }

  *argsCurrent = NULL;

  int status = execute(argsBuffer[0], argsBuffer);

  if ((flags & flag_throw) && status != 0)
    throw torrent::input_error("Bad return code.");

  return torrent::Object((int64_t)status);
}

}
