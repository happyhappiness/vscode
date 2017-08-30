      fprintf(stderr, "  item %d [%s]\n", i,

              this->EntryList[i].Item.c_str());

      }

    NodeList const& ol = this->CCG->GetComponentGraphEdges(c);

    for(NodeList::const_iterator oi = ol.begin(); oi != ol.end(); ++oi)

      {

      fprintf(stderr, "  followed by Component (%d)\n", *oi);

      }

    fprintf(stderr, "  topo order index %d\n",

            this->ComponentOrder[c]);

