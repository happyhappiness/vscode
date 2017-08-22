  return count;
}

//----------------------------------------------------------------------------
void cmComputeLinkDepends::DisplayFinalEntries()
{
  fprintf(stderr, "target [%s] links to:\n", this->Target->GetName().c_str());
