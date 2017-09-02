std::vector<cmComputeLinkDepends::LinkEntry> const&
cmComputeLinkDepends::Compute()
{
  // Follow the link dependencies of the target to be linked.
  this->AddDirectLinkEntries();

  // Complete the breadth-first search of dependencies.
  while(!this->BFSQueue.empty())
    {
    // Get the next entry.
    BFSEntry qe = this->BFSQueue.front();
    this->BFSQueue.pop();

    // Follow the entry's dependencies.
    this->FollowLinkEntry(qe);
    }

  // Complete the search of shared library dependencies.
  while(!this->SharedDepQueue.empty())
    {
    // Handle the next entry.
    this->HandleSharedDependency(this->SharedDepQueue.front());
    this->SharedDepQueue.pop();
    }

  // Infer dependencies of targets for which they were not known.
  this->InferDependencies();

  // Cleanup the constraint graph.
  this->CleanConstraintGraph();

  // Display the constraint graph.
  if(this->DebugMode)
    {
    fprintf(stderr,
            "---------------------------------------"
            "---------------------------------------\n");
    fprintf(stderr, "Link dependency analysis for target %s, config %s\n",
            this->Target->GetName().c_str(),
            this->Config?this->Config:"noconfig");
    this->DisplayConstraintGraph();
    }

  // Compute the final ordering.
  this->OrderLinkEntires();

  // Compute the final set of link entries.
  for(std::vector<int>::const_iterator li = this->FinalLinkOrder.begin();
      li != this->FinalLinkOrder.end(); ++li)
    {
    this->FinalLinkEntries.push_back(this->EntryList[*li]);
    }

  // Display the final set.
  if(this->DebugMode)
    {
    this->DisplayFinalEntries();
    }

  return this->FinalLinkEntries;
}