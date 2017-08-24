{
    CommandLineArgumentsCallbackStructure* cs = &(it->second);
    mpit = mp.find(cs->Help);
    if (mpit != mp.end()) {
      mpit->second.insert(it->first);
      mp[it->first].insert(it->first);
    } else {
      mp[it->first].insert(it->first);
    }
  }