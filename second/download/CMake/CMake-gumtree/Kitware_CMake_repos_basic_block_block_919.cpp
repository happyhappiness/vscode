(cc = 0; cc < this->Internals->UnusedArguments.size(); cc++) {
    kwsys::String& str = this->Internals->UnusedArguments[cc];
    args[cnt] = new char[str.size() + 1];
    strcpy(args[cnt], str.c_str());
    cnt++;
  }