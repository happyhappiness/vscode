(mpit != mp.end()) {
      mpit->second.insert(it->first);
      smpit = mp.find(it->first);
      CommandLineArguments::Internal::SetOfStrings::iterator sit;
      for (sit = smpit->second.begin(); sit != smpit->second.end(); sit++) {
        mpit->second.insert(*sit);
      }
      mp.erase(smpit);
    } else {
      mp[it->first].insert(it->first);
    }