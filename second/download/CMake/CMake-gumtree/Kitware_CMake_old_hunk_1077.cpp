    e << "item " << i << " is [" << this->EntryList[i].Item << "]\n";
    for(NodeList::const_iterator j = nl.begin(); j != nl.end(); ++j)
      {
      e << "  item " << *j << " must precede it\n";
      }
    }
  fprintf(stderr, "%s\n", e.str().c_str());
