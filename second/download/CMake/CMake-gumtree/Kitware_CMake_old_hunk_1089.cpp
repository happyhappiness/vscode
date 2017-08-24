  int dependee_index = tii->second;

  // Add this entry to the dependency graph.
  this->TargetDependGraph[depender_index].push_back(dependee_index);
}

//----------------------------------------------------------------------------
void
cmComputeTargetDepends
::DisplayGraph(std::vector<TargetDependList> const& graph,
               const char* name)
{
  fprintf(stderr, "The %s target dependency graph is:\n", name);
  int n = static_cast<int>(graph.size());
  for(int depender_index = 0; depender_index < n; ++depender_index)
    {
    TargetDependList const& tdl = graph[depender_index];
    cmTarget* depender = this->Targets[depender_index];
    fprintf(stderr, "target %d is [%s]\n",
            depender_index, depender->GetName());
    for(TargetDependList::const_iterator di = tdl.begin();
        di != tdl.end(); ++di)
      {
      int dependee_index = *di;
      cmTarget* dependee = this->Targets[dependee_index];
      fprintf(stderr, "  depends on target %d [%s]\n", dependee_index,
              dependee->GetName());
