      fprintf(stderr, "  item %d [%s]\n", i,
              this->EntryList[i].Item.c_str());
      }
    }
  fprintf(stderr, "\n");
}

//----------------------------------------------------------------------------
void
cmComputeLinkDepends::VisitComponent(cmComputeComponentGraph const& ccg,
                                     unsigned int c)
{
  // Check if the node has already been visited.
  if(this->ComponentVisited[c])
