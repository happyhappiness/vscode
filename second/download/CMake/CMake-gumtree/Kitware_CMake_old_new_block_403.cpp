{
    EdgeList const& nl = graph[depender_index];
    cmTarget const* depender = this->Targets[depender_index];
    fprintf(stderr, "target %d is [%s]\n",
            depender_index, depender->GetName());
    for(EdgeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
      {
      int dependee_index = *ni;
      cmTarget const* dependee = this->Targets[dependee_index];
      fprintf(stderr, "  depends on target %d [%s] (%s)\n", dependee_index,
              dependee->GetName(), ni->IsStrong()? "strong" : "weak");
      }
    }