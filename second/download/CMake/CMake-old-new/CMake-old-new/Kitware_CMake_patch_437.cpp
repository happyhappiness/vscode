@@ -35,7 +35,7 @@ cmDependsJavaParserHelper::~cmDependsJavaParserHelper()
 }
 
 void cmDependsJavaParserHelper::CurrentClass
-::AddFileNamesForPrinting(std::vector<cmStdString> *files, 
+::AddFileNamesForPrinting(std::vector<cmStdString> *files,
                           const char* prefix, const char* sep)
 {
   cmStdString rname = "";
@@ -103,7 +103,7 @@ void cmDependsJavaParserHelper::AddPackagesImport(const char* sclass)
   this->PackagesImport.push_back(sclass);
 }
 
-void cmDependsJavaParserHelper::SafePrintMissing(const char* str, 
+void cmDependsJavaParserHelper::SafePrintMissing(const char* str,
                                                  int line, int cnt)
 {
   if ( str )
@@ -134,7 +134,7 @@ void cmDependsJavaParserHelper::Print(const char* place, const char* str)
     }
 }
 
-void cmDependsJavaParserHelper::CombineUnions(char** out, 
+void cmDependsJavaParserHelper::CombineUnions(char** out,
                                               const char* in1, char** in2,
                                               const char* sep)
 {
@@ -193,7 +193,7 @@ ::PrepareElement(cmDependsJavaParserHelper::ParserType* me)
 }
 
 void cmDependsJavaParserHelper
-::AllocateParserType(cmDependsJavaParserHelper::ParserType* pt, 
+::AllocateParserType(cmDependsJavaParserHelper::ParserType* pt,
                      const char* str, int len)
 {
   pt->str = 0;
@@ -270,7 +270,7 @@ std::vector<cmStdString> cmDependsJavaParserHelper::GetFilesProduced()
   std::vector<cmStdString> files;
   CurrentClass* toplevel = &(*(this->ClassStack.begin()));
   std::vector<CurrentClass>::iterator it;
-  for ( it = toplevel->NestedClasses->begin(); 
+  for ( it = toplevel->NestedClasses->begin();
     it != toplevel->NestedClasses->end();
     ++ it )
     {
@@ -289,7 +289,7 @@ int cmDependsJavaParserHelper::ParseString(const char* str, int verb)
   this->InputBuffer = str;
   this->InputBufferPos = 0;
   this->CurrentLine = 0;
-  
+
 
   yyscan_t yyscanner;
   cmDependsJava_yylex_init(&yyscanner);
@@ -306,7 +306,7 @@ int cmDependsJavaParserHelper::ParseString(const char* str, int verb)
     {
     if ( this->CurrentPackage.size() > 0 )
       {
-      std::cout << "Current package is: " << 
+      std::cout << "Current package is: " <<
         this->CurrentPackage.c_str() << std::endl;
       }
     std::cout << "Imports packages:";
@@ -337,7 +337,7 @@ int cmDependsJavaParserHelper::ParseString(const char* str, int verb)
     this->PrintClasses();
     if ( this->UnionsAvailable != 0 )
       {
-      std::cout << "There are still " << 
+      std::cout << "There are still " <<
         this->UnionsAvailable << " unions available" << std::endl;
       }
     }
@@ -348,13 +348,13 @@ int cmDependsJavaParserHelper::ParseString(const char* str, int verb)
 void cmDependsJavaParserHelper::CleanupParser()
 {
   std::vector<char*>::iterator it;
-  for ( it = this->Allocates.begin(); 
+  for ( it = this->Allocates.begin();
     it != this->Allocates.end();
     ++ it )
     {
     delete [] *it;
     }
-  this->Allocates.erase(this->Allocates.begin(), 
+  this->Allocates.erase(this->Allocates.begin(),
     this->Allocates.end());
 }
 
@@ -382,11 +382,11 @@ int cmDependsJavaParserHelper::LexInput(char* buf, int maxlen)
 void cmDependsJavaParserHelper::Error(const char* str)
 {
   unsigned long pos = static_cast<unsigned long>(this->InputBufferPos);
-  fprintf(stderr, "JPError: %s (%lu / Line: %d)\n", 
+  fprintf(stderr, "JPError: %s (%lu / Line: %d)\n",
           str, pos, this->CurrentLine);
   int cc;
   std::cerr << "String: [";
-  for ( cc = 0; 
+  for ( cc = 0;
         cc < 30 && *(this->InputBuffer.c_str() + this->InputBufferPos + cc);
         cc ++ )
     {
@@ -395,7 +395,7 @@ void cmDependsJavaParserHelper::Error(const char* str)
   std::cerr << "]" << std::endl;
 }
 
-void cmDependsJavaParserHelper::UpdateCombine(const char* str1, 
+void cmDependsJavaParserHelper::UpdateCombine(const char* str1,
                                               const char* str2)
 {
   if ( this->CurrentCombine == "" && str1 != 0)