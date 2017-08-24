}

//----------------------------------------------------------------------------
void
cmComputeTargetDepends
::DisplayComponents(cmComputeComponentGraph const& ccg)
{
  fprintf(stderr, "The strongly connected components are:\n");
  std::vector<NodeList> const& components = ccg.GetComponents();
  int n = static_cast<int>(components.size());
  for(int c = 0; c < n; ++c)
    {
    NodeList const& nl = components[c];
    fprintf(stderr, "Component (%d):\n", c);
    for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
      {
      int i = *ni;
      fprintf(stderr, "  contains target %d [%s]\n",
              i, this->Targets[i]->GetName());
      }
