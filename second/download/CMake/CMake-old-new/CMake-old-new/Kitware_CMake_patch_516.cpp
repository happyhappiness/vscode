@@ -63,7 +63,8 @@ char* cmCommandArgumentParserHelper::AddString(const char* str)
   return stVal;
 }
 
-char* cmCommandArgumentParserHelper::ExpandSpecialVariable(const char* key, const char* var)
+char* cmCommandArgumentParserHelper::ExpandSpecialVariable(const char* key, 
+                                                           const char* var)
 {
   if ( !key )
     {
@@ -85,7 +86,8 @@ char* cmCommandArgumentParserHelper::ExpandSpecialVariable(const char* key, cons
       }
     return this->EmptyVariable;
     }
-  cmSystemTools::Error("Key ", key, " is not used yet. For now only $ENV{..} is allowed");
+  cmSystemTools::Error("Key ", key, 
+                       " is not used yet. For now only $ENV{..} is allowed");
   return 0;
 }
 
@@ -131,8 +133,8 @@ char* cmCommandArgumentParserHelper::CombineUnions(char* in1, char* in2)
   return out;
 }
 
-void cmCommandArgumentParserHelper::AllocateParserType(cmCommandArgumentParserHelper::ParserType* pt, 
-  const char* str, int len)
+void cmCommandArgumentParserHelper::AllocateParserType
+(cmCommandArgumentParserHelper::ParserType* pt,const char* str, int len)
 {
   pt->str = 0;
   if ( len == 0 )
@@ -147,10 +149,10 @@ void cmCommandArgumentParserHelper::AllocateParserType(cmCommandArgumentParserHe
   strncpy(pt->str, str, len);
   pt->str[len] = 0;
   this->Variables.push_back(pt->str);
-  // std::cout << (void*) pt->str << " " << pt->str << " JPAllocateParserType" << std::endl;
 }
 
-bool cmCommandArgumentParserHelper::HandleEscapeSymbol(cmCommandArgumentParserHelper::ParserType* pt, char symbol)
+bool cmCommandArgumentParserHelper::HandleEscapeSymbol
+(cmCommandArgumentParserHelper::ParserType* pt, char symbol)
 {
   if ( this->NoEscapeMode )
     {
@@ -204,8 +206,6 @@ int cmCommandArgumentParserHelper::ParseString(const char* str, int verb)
     {
     return 0;
     }
-  //printf("Do some parsing: %s\n", str);
-
   this->Verbose = verb;
   this->InputBuffer = str;
   this->InputBufferPos = 0;
@@ -220,16 +220,15 @@ int cmCommandArgumentParserHelper::ParseString(const char* str, int verb)
   cmCommandArgument_yylex_destroy(yyscanner);
   if ( res != 0 )
     {
-    //str << "CAL_Parser returned: " << res << std::endl;
-    //std::cerr << "When parsing: [" << str << "]" << std::endl;
     return 0;
     }
 
   this->CleanupParser();
 
   if ( Verbose )
     {
-    std::cerr << "Expanding [" << str << "] produced: [" << this->Result.c_str() << "]" << std::endl;
+    std::cerr << "Expanding [" << str << "] produced: [" 
+              << this->Result.c_str() << "]" << std::endl;
     }
   return 1;
 }
@@ -248,9 +247,6 @@ void cmCommandArgumentParserHelper::CleanupParser()
 
 int cmCommandArgumentParserHelper::LexInput(char* buf, int maxlen)
 {
-  //std::cout << "JPLexInput ";
-  //std::cout.write(buf, maxlen);
-  //std::cout << std::endl;
   if ( maxlen < 1 )
     {
     return 0;
@@ -274,19 +270,8 @@ int cmCommandArgumentParserHelper::LexInput(char* buf, int maxlen)
 void cmCommandArgumentParserHelper::Error(const char* str)
 {
   unsigned long pos = static_cast<unsigned long>(this->InputBufferPos);
-  //fprintf(stderr, "Argument Parser Error: %s (%lu / Line: %d)\n", str, pos, this->CurrentLine);
   cmOStringStream ostr;
   ostr << str << " (" << pos << ")";
-  /*
-  int cc;
-  std::cerr << "String: [";
-  for ( cc = 0; cc < 30 && *(this->InputBuffer.c_str() + this->InputBufferPos + cc);
-    cc ++ )
-    {
-    std::cerr << *(this->InputBuffer.c_str() + this->InputBufferPos + cc);
-    }
-  std::cerr << "]" << std::endl;
-  */
   this->ErrorString = ostr.str();
 }
 