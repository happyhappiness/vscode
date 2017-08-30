{
  if ( !name )
    {
      fprintf(stderr, "*** 1 name==0\n");
    return 0;
    }
      fprintf(stderr, "*** 2 name==%s\n", name);
  cmCPackGenerators::t_GeneratorCreatorsMap::iterator it
    = this->GeneratorCreators.find(name);
  if ( it == this->GeneratorCreators.end() )
    {
      fprintf(stderr, "*** 2 name==%s not found\n", name);
    return 0;
    }
  return (it->second)();