      fprintf(stderr, "  item %d [%s]\n", i,
              this->EntryList[i].Item.c_str());
      }
    EdgeList const& ol = this->CCG->GetComponentGraphEdges(c);
    for(EdgeList::const_iterator oi = ol.begin(); oi != ol.end(); ++oi)
      {
      fprintf(stderr, "  followed by Component (%d)\n", *oi);
      }
