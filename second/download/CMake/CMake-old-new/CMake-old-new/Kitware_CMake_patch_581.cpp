@@ -26,6 +26,8 @@ int cmCommandArgument_yyparse( yyscan_t yyscanner );
 cmCommandArgumentParserHelper::cmCommandArgumentParserHelper()
 {
   m_FileLine = -1;
+  m_FileName = 0;
+  m_EmptyVariable[0] = 0;
 }
 
 
@@ -79,17 +81,21 @@ char* cmCommandArgumentParserHelper::ExpandSpecialVariable(const char* key, cons
 
 char* cmCommandArgumentParserHelper::ExpandVariable(const char* var)
 {
-  if(var == "CMAKE_CURRENT_LIST_FILE")
+  if(m_FileName && strcmp(var, "CMAKE_CURRENT_LIST_FILE") == 0)
     {
-    return this->AddString(m_FileName.c_str());
+    return this->AddString(m_FileName);
     }
-  else if(m_FileLine >= 0 && (var == "CMAKE_CURRENT_LIST_LINE"))
+  else if(m_FileLine >= 0 && strcmp(var, "CMAKE_CURRENT_LIST_LINE") == 0)
     {
     cmOStringStream ostr;
     ostr << m_FileLine;
     return this->AddString(ostr.str().c_str());
     } 
   const char* value = m_Makefile->GetDefinition(var);
+  if (m_EscapeQuotes)
+    {
+    return this->AddString(cmSystemTools::EscapeQuotes(value).c_str());
+    }
   return this->AddString(value);
 }
 
@@ -228,7 +234,8 @@ int cmCommandArgumentParserHelper::ParseString(const char* str, int verb)
   cmCommandArgument_yylex_destroy(yyscanner);
   if ( res != 0 )
     {
-    std::cout << "JP_Parse returned: " << res << std::endl;
+    std::cerr << "CAL_Parser returned: " << res << std::endl;
+    std::cerr << "When parsing: [" << str << "]" << std::endl;
     return 0;
     }
 
@@ -289,7 +296,7 @@ int cmCommandArgumentParserHelper::LexInput(char* buf, int maxlen)
 void cmCommandArgumentParserHelper::Error(const char* str)
 {
   unsigned long pos = static_cast<unsigned long>(this->InputBufferPos);
-  fprintf(stderr, "JPError: %s (%lu / Line: %d)\n", str, pos, this->CurrentLine);
+  fprintf(stderr, "Argument Parser Error: %s (%lu / Line: %d)\n", str, pos, this->CurrentLine);
   int cc;
   std::cerr << "String: [";
   for ( cc = 0; cc < 30 && *(this->InputBuffer.c_str() + this->InputBufferPos + cc);
@@ -345,6 +352,7 @@ void cmCommandArgumentParserHelper::SetResult(const char* value)
 {
   if ( !value )
     {
+    m_Result = "";
     return;
     }
   m_Result = value;