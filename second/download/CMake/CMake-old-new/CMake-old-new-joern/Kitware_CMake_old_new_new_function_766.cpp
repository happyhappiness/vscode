void
cmComputeTargetDepends::DisplayGraph(Graph const& graph,
                                     const std::string& name)
{
  fprintf(stderr, "The %s target dependency graph is:\n", name.c_str());
  int n = static_cast<int>(graph.size());
  for(int depender_index = 0; depender_index < n; ++depender_index)
    {
    EdgeList const& nl = graph[depender_index];
    cmTarget const* depender = this->Targets[depender_index];
    fprintf(stderr, "target %d is [%s]\n",
            depender_index, depender->GetName().c_str());
    for(EdgeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
      {
      int dependee_index = *ni;
      cmTarget const* dependee = this->Targets[dependee_index];
      fprintf(stderr, "  depends on target %d [%s] (%s)\n", dependee_index,
              dependee->GetName().c_str(), ni->IsStrong()? "strong" : "weak");
      }
    }
  fprintf(stderr, "\n");
}