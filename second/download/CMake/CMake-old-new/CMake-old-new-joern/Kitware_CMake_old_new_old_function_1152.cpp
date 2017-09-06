cmCPackGenericGenerator* cmCPackGenerators::NewGenerator(const char* name)
{
  cmCPackGenericGenerator* gen = this->NewGeneratorInternal(name);
  fprintf(stderr, "********* NewGen %s\n", name);
  if ( !gen )
    {
    return 0;
    }
  this->Generators.push_back(gen);
  gen->SetLogger(this->Logger);
  return gen;
}