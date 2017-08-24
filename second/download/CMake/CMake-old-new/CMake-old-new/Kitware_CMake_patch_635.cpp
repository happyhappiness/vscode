@@ -27,7 +27,14 @@ cmCommandArgumentParserHelper::cmCommandArgumentParserHelper()
 {
   m_FileLine = -1;
   m_FileName = 0;
+
   m_EmptyVariable[0] = 0;
+  strcpy(m_DCURLYVariable, "${");
+  strcpy(m_RCURLYVariable, "}");
+  strcpy(m_ATVariable,     "@");
+  strcpy(m_DOLLARVariable, "$");
+  strcpy(m_LCURLYVariable, "{");
+  strcpy(m_BSLASHVariable, "\\");
 }
 
 
@@ -234,8 +241,8 @@ int cmCommandArgumentParserHelper::ParseString(const char* str, int verb)
   cmCommandArgument_yylex_destroy(yyscanner);
   if ( res != 0 )
     {
-    std::cerr << "CAL_Parser returned: " << res << std::endl;
-    std::cerr << "When parsing: [" << str << "]" << std::endl;
+    //str << "CAL_Parser returned: " << res << std::endl;
+    //std::cerr << "When parsing: [" << str << "]" << std::endl;
     return 0;
     }
 
@@ -296,7 +303,10 @@ int cmCommandArgumentParserHelper::LexInput(char* buf, int maxlen)
 void cmCommandArgumentParserHelper::Error(const char* str)
 {
   unsigned long pos = static_cast<unsigned long>(this->InputBufferPos);
-  fprintf(stderr, "Argument Parser Error: %s (%lu / Line: %d)\n", str, pos, this->CurrentLine);
+  //fprintf(stderr, "Argument Parser Error: %s (%lu / Line: %d)\n", str, pos, this->CurrentLine);
+  cmOStringStream ostr;
+  ostr << str << " (" << pos << ")";
+  /*
   int cc;
   std::cerr << "String: [";
   for ( cc = 0; cc < 30 && *(this->InputBuffer.c_str() + this->InputBufferPos + cc);
@@ -305,6 +315,8 @@ void cmCommandArgumentParserHelper::Error(const char* str)
     std::cerr << *(this->InputBuffer.c_str() + this->InputBufferPos + cc);
     }
   std::cerr << "]" << std::endl;
+  */
+  m_Error = ostr.str();
 }
 
 void cmCommandArgumentParserHelper::UpdateCombine(const char* str1, const char* str2)