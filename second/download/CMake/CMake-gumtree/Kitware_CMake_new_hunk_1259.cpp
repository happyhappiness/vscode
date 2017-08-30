      fprintf(stderr, "  item %d [%s]\n", i,

              this->EntryList[i].Item.c_str());

      }

    EdgeList const& ol = this->CCG->GetComponentGraphEdges(c);

    for(EdgeList::const_iterator oi = ol.begin(); oi != ol.end(); ++oi)

      {

      int i = *oi;

      fprintf(stderr, "  followed by Component (%d)\n", i);

      }

    fprintf(stderr, "  topo order index %d\n",

            this->ComponentOrder[c]);

