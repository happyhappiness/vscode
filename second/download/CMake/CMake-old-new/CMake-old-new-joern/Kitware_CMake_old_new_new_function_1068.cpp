void
cmComputeLinkDepends::DisplayComponents()
{
  fprintf(stderr, "The strongly connected components are:\n");
  std::vector<NodeList> const& components = this->CCG->GetComponents();
  for(unsigned int c=0; c < components.size(); ++c)
    {
    fprintf(stderr, "Component (%u):\n", c);
    NodeList const& nl = components[c];
    for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
      {
      int i = *ni;
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
    }
  fprintf(stderr, "\n");
}