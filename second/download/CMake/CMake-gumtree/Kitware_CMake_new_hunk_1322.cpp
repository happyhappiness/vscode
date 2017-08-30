  // the same order in which the items were originally discovered in
  // the BFS.  This should preserve the original order when no
  // constraints disallow it.
  this->CCG = new cmComputeComponentGraph(this->EntryConstraintGraph);

  // The component graph is guaranteed to be acyclic.  Start a DFS
  // from every entry to compute a topological order for the
  // components.
  Graph const& cgraph = this->CCG->GetComponentGraph();
  int n = static_cast<int>(cgraph.size());
  this->ComponentVisited.resize(cgraph.size(), 0);
  this->ComponentOrder.resize(cgraph.size(), n);
  this->ComponentOrderId = n;
  // Run in reverse order so the topological order will preserve the
  // original order where there are no constraints.
  for(int c = n-1; c >= 0; --c)
    {
    this->VisitComponent(c);
    }

  // Display the component graph.
  if(this->DebugMode)
    {
    this->DisplayComponents();
    }

  // Start with the original link line.
  for(std::vector<int>::const_iterator i = this->OriginalEntries.begin();
      i != this->OriginalEntries.end(); ++i)
    {
    this->VisitEntry(*i);
    }

  // Now explore anything left pending.  Since the component graph is
  // guaranteed to be acyclic we know this will terminate.
  while(!this->PendingComponents.empty())
    {
    // Visit one entry from the first pending component.  The visit
    // logic will update the pending components accordingly.  Since
    // the pending components are kept in topological order this will
    // not repeat one.
    int e = *this->PendingComponents.begin()->second.Entries.begin();
    this->VisitEntry(e);
    }
}

//----------------------------------------------------------------------------
void
cmComputeLinkDepends::DisplayComponents()
{
  fprintf(stderr, "The strongly connected components are:\n");
  std::vector<NodeList> const& components = this->CCG->GetComponents();
  for(unsigned int c=0; c < components.size(); ++c)
    {
    fprintf(stderr, "Component (%u):\n", c);
