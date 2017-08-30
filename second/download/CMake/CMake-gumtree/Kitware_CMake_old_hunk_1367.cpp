cmCPackGenericGenerator* cmCPackGenerators::NewGenerator(const char* name)

{

  cmCPackGenericGenerator* gen = this->NewGeneratorInternal(name);

  fprintf(stderr, "********* NewGen %s\n", name);

  if ( !gen )

    {

    return 0;

