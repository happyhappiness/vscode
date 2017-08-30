  // the same order in which the items were originally discovered in
  // the BFS.  This should preserve the original order when no
  // constraints disallow it.
  cmComputeComponentGraph ccg(this->EntryConstraintGraph);
  Graph const& cgraph = ccg.GetComponentGraph();
  if(this->DebugMode)
    {
    this->DisplayComponents(ccg);
    }

  // Setup visit tracking.
  this->ComponentVisited.resize(cgraph.size(), 0);

  // The component graph is guaranteed to be acyclic.  Start a DFS
  // from every entry.
  for(unsigned int c=0; c < cgraph.size(); ++c)
    {
    this->VisitComponent(ccg, c);
    }
}

//----------------------------------------------------------------------------
void
cmComputeLinkDepends::DisplayComponents(cmComputeComponentGraph const& ccg)
{
  fprintf(stderr, "The strongly connected components are:\n");
  std::vector<NodeList> const& components = ccg.GetComponents();
  for(unsigned int c=0; c < components.size(); ++c)
    {
    fprintf(stderr, "Component (%u):\n", c);
