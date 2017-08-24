{
    CommandLineArguments::Internal::CallbacksMap::iterator hit =
      this->Internals->Callbacks.find(cs->Help);
    if (hit == this->Internals->Callbacks.end()) {
      break;
    }
    cs = &(hit->second);
  }