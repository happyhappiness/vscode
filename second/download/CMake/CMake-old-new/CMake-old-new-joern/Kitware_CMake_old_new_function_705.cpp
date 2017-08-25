void cmComputeTargetDepends::DisplayComponents()
{
  fprintf(stderr, "The strongly connected components are:\n");
  int n = static_cast<int>(this->Components.size());
  for(int c = 0; c < n; ++c)
    {
    ComponentList const& cl = this->Components[c];
    fprintf(stderr, "Component (%d):\n", c);
    for(ComponentList::const_iterator ci = cl.begin();
        ci != cl.end(); ++ci)
      {
      int i = *ci;
      fprintf(stderr, "  contains target %d [%s]\n",
              i, this->Targets[i]->GetName());
      }
    }
  fprintf(stderr, "\n");
}