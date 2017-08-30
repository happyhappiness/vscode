cmCPackGenericGenerator* cmCPackGenerators::NewGenerator(const char* name)

{

  cmCPackGenericGenerator* gen = this->NewGeneratorInternal(name);

  if ( !gen )

    {

    return 0;

