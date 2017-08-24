void
cmComputeLinkDepends::DisplayComponents(cmComputeComponentGraph const& ccg)
{
  fprintf(stderr, "The strongly connected components are:\n");
  std::vector<NodeList> const& components = ccg.GetComponents();
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
    }
  fprintf(stderr, "\n");
}