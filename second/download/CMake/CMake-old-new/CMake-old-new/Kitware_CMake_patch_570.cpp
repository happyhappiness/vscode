@@ -39,7 +39,9 @@ cmDependsJavaParserHelper::~cmDependsJavaParserHelper()
   this->CleanupParser();
 }
 
-void cmDependsJavaParserHelper::CurrentClass::AddFileNamesForPrinting(std::vector<cmStdString> *files, const char* prefix, const char* sep)
+void cmDependsJavaParserHelper::CurrentClass
+::AddFileNamesForPrinting(std::vector<cmStdString> *files, 
+                          const char* prefix, const char* sep)
 {
   cmStdString rname = "";
   if ( prefix )
@@ -66,11 +68,8 @@ void cmDependsJavaParserHelper::DeallocateParserType(char** pt)
     }
   if (!*pt)
     {
-    //*pt = 0;
     return;
     }
-  // std::cout << (void*) *pt << " " << *pt << " this->DeallocateParserType" << std::endl;
-  //delete [] *pt;
   *pt = 0;
   this->UnionsAvailable --;
 }
@@ -109,11 +108,11 @@ void cmDependsJavaParserHelper::AddPackagesImport(const char* sclass)
   this->PackagesImport.push_back(sclass);
 }
 
-void cmDependsJavaParserHelper::SafePrintMissing(const char* str, int line, int cnt)
+void cmDependsJavaParserHelper::SafePrintMissing(const char* str, 
+                                                 int line, int cnt)
 {
   if ( str )
     {
-    //std::cout << (void*) str << " JPSafePrintMissing" << std::endl;
     std::cout << line << " String " << cnt << " exists: ";
     unsigned int cc;
     for ( cc = 0; cc < strlen(str); cc ++ )
@@ -140,8 +139,9 @@ void cmDependsJavaParserHelper::Print(const char* place, const char* str)
     }
 }
 
-void cmDependsJavaParserHelper::CombineUnions(char** out, const char* in1, char** in2,
-  const char* sep)
+void cmDependsJavaParserHelper::CombineUnions(char** out, 
+                                              const char* in1, char** in2,
+                                              const char* sep)
 {
   size_t len = 1;
   if ( in1 )
@@ -174,11 +174,11 @@ void cmDependsJavaParserHelper::CombineUnions(char** out, const char* in1, char*
     {
     this->DeallocateParserType(in2);
     }
-  // std::cout << (void*) *out << " " << *out << " JPAllocateParserType" << std::endl;
   this->UnionsAvailable ++;
 }
 
-void cmDependsJavaParserHelper::CheckEmpty(int line, int cnt, cmDependsJavaParserHelper::ParserType* pt)
+void cmDependsJavaParserHelper
+::CheckEmpty(int line, int cnt, cmDependsJavaParserHelper::ParserType* pt)
 {
   int cc;
   int kk = -cnt + 1;
@@ -190,14 +190,16 @@ void cmDependsJavaParserHelper::CheckEmpty(int line, int cnt, cmDependsJavaParse
     }
 }
 
-void cmDependsJavaParserHelper::PrepareElement(cmDependsJavaParserHelper::ParserType* me)
+void cmDependsJavaParserHelper
+::PrepareElement(cmDependsJavaParserHelper::ParserType* me)
 {
   // Inititalize self
   me->str = 0;
 }
 
-void cmDependsJavaParserHelper::AllocateParserType(cmDependsJavaParserHelper::ParserType* pt, 
-  const char* str, int len)
+void cmDependsJavaParserHelper
+::AllocateParserType(cmDependsJavaParserHelper::ParserType* pt, 
+                     const char* str, int len)
 {
   pt->str = 0;
   if ( len == 0 )
@@ -213,7 +215,6 @@ void cmDependsJavaParserHelper::AllocateParserType(cmDependsJavaParserHelper::Pa
   strncpy(pt->str, str, len);
   pt->str[len] = 0;
   this->Allocates.push_back(pt->str);
-  // std::cout << (void*) pt->str << " " << pt->str << " JPAllocateParserType" << std::endl;
 }
 
 void cmDependsJavaParserHelper::StartClass(const char* cls)
@@ -289,8 +290,6 @@ int cmDependsJavaParserHelper::ParseString(const char* str, int verb)
     {
     return 0;
     }
-  //printf("Do some parsing: %s\n", str);
-
   this->Verbose = verb;
   this->InputBuffer = str;
   this->InputBufferPos = 0;
@@ -312,7 +311,8 @@ int cmDependsJavaParserHelper::ParseString(const char* str, int verb)
     {
     if ( this->CurrentPackage.size() > 0 )
       {
-      std::cout << "Current package is: " << this->CurrentPackage.c_str() << std::endl;
+      std::cout << "Current package is: " << 
+        this->CurrentPackage.c_str() << std::endl;
       }
     std::cout << "Imports packages:";
     if ( this->PackagesImport.size() > 0 )
@@ -342,8 +342,8 @@ int cmDependsJavaParserHelper::ParseString(const char* str, int verb)
     this->PrintClasses();
     if ( this->UnionsAvailable != 0 )
       {
-      std::cout << "There are still " << this->UnionsAvailable << " unions available" << std::endl;
-      //return 0;
+      std::cout << "There are still " << 
+        this->UnionsAvailable << " unions available" << std::endl;
       }
     }
   this->CleanupParser();
@@ -365,9 +365,6 @@ void cmDependsJavaParserHelper::CleanupParser()
 
 int cmDependsJavaParserHelper::LexInput(char* buf, int maxlen)
 {
-  //std::cout << "JPLexInput ";
-  //std::cout.write(buf, maxlen);
-  //std::cout << std::endl;
   if ( maxlen < 1 )
     {
     return 0;
@@ -390,18 +387,21 @@ int cmDependsJavaParserHelper::LexInput(char* buf, int maxlen)
 void cmDependsJavaParserHelper::Error(const char* str)
 {
   unsigned long pos = static_cast<unsigned long>(this->InputBufferPos);
-  fprintf(stderr, "JPError: %s (%lu / Line: %d)\n", str, pos, this->CurrentLine);
+  fprintf(stderr, "JPError: %s (%lu / Line: %d)\n", 
+          str, pos, this->CurrentLine);
   int cc;
   std::cerr << "String: [";
-  for ( cc = 0; cc < 30 && *(this->InputBuffer.c_str() + this->InputBufferPos + cc);
-    cc ++ )
+  for ( cc = 0; 
+        cc < 30 && *(this->InputBuffer.c_str() + this->InputBufferPos + cc);
+        cc ++ )
     {
     std::cerr << *(this->InputBuffer.c_str() + this->InputBufferPos + cc);
     }
   std::cerr << "]" << std::endl;
 }
 
-void cmDependsJavaParserHelper::UpdateCombine(const char* str1, const char* str2)
+void cmDependsJavaParserHelper::UpdateCombine(const char* str1, 
+                                              const char* str2)
 {
   if ( this->CurrentCombine == "" && str1 != 0)
     {