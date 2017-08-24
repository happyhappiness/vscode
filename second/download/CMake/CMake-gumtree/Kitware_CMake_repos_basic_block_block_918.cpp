{
    args[cnt] = new char[this->Internals->Argv[cc].size() + 1];
    strcpy(args[cnt], this->Internals->Argv[cc].c_str());
    cnt++;
  }