@@ -90,7 +90,6 @@ cmCPackGenerators::~cmCPackGenerators()
 cmCPackGenericGenerator* cmCPackGenerators::NewGenerator(const char* name)
 {
   cmCPackGenericGenerator* gen = this->NewGeneratorInternal(name);
-  fprintf(stderr, "********* NewGen %s\n", name);
   if ( !gen )
     {
     return 0;
@@ -106,15 +105,12 @@ cmCPackGenericGenerator* cmCPackGenerators::NewGeneratorInternal(
 {
   if ( !name )
     {
-      fprintf(stderr, "*** 1 name==0\n");
     return 0;
     }
-      fprintf(stderr, "*** 2 name==%s\n", name);
   cmCPackGenerators::t_GeneratorCreatorsMap::iterator it
     = this->GeneratorCreators.find(name);
   if ( it == this->GeneratorCreators.end() )
     {
-      fprintf(stderr, "*** 2 name==%s not found\n", name);
     return 0;
     }
   return (it->second)();