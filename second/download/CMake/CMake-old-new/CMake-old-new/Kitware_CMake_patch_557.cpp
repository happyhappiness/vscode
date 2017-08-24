@@ -39,14 +39,14 @@
 #include <string.h>
 namespace KWSYS_NAMESPACE
 {
-#if defined( _WIN32 ) || defined( APPLE ) || defined( __CYGWIN__ )
-  // On Windows and apple, no difference between lower and upper case
-  #define KWSYS_GLOB_CASE_INDEPENDENT
+#if defined(_WIN32) || defined(APPLE) || defined(__CYGWIN__)
+// On Windows and apple, no difference between lower and upper case
+# define KWSYS_GLOB_CASE_INDEPENDENT
 #endif
 
-#if defined( _WIN32 ) || defined( __CYGWIN__ )
-  // Handle network paths
-  #define KWSYS_GLOB_SUPPORT_NETWORK_PATHS
+#if defined(_WIN32) || defined(__CYGWIN__)
+// Handle network paths
+# define KWSYS_GLOB_SUPPORT_NETWORK_PATHS
 #endif
 
 //----------------------------------------------------------------------------
@@ -55,7 +55,6 @@ class GlobInternals
 public:
   kwsys_stl::vector<kwsys_stl::string> Files;
   kwsys_stl::vector<kwsys::RegularExpression> Expressions;
-  kwsys_stl::vector<kwsys_stl::string> TextExpressions;
 };
 
 //----------------------------------------------------------------------------
@@ -73,109 +72,132 @@ Glob::~Glob()
 }
 
 //----------------------------------------------------------------------------
-void Glob::Escape(int ch, char* buffer)
-{
-  if (! (
-      'a' <= ch && ch <= 'z' ||
-      'A' <= ch && ch <= 'Z' ||
-      '0' <= ch && ch <= '9') )
-    {
-    sprintf(buffer, "\\%c", ch);
-    }
-  else
-    {
-#if defined( KWSYS_GLOB_CASE_INDEPENDENT )
-    // On Windows and apple, no difference between lower and upper case
-    sprintf(buffer, "%c", tolower(ch));
-#else
-    sprintf(buffer, "%c", ch);
-#endif
-    }
-}
-
-//----------------------------------------------------------------------------
 kwsys_stl::vector<kwsys_stl::string>& Glob::GetFiles()
 {
   return this->Internals->Files;
 }
 
 //----------------------------------------------------------------------------
-kwsys_stl::string Glob::ConvertExpression(const kwsys_stl::string& expr)
+kwsys_stl::string Glob::PatternToRegex(const kwsys_stl::string& pattern,
+                                       bool require_whole_string)
 {
-
-  kwsys_stl::string::size_type i = 0;
-  kwsys_stl::string::size_type n = expr.size();
-
-  kwsys_stl::string res = "^";
-  kwsys_stl::string stuff = "";
-
-  while ( i < n )
+  // Incrementally build the regular expression from the pattern.
+  kwsys_stl::string regex = require_whole_string? "^" : "";
+  kwsys_stl::string::const_iterator pattern_first = pattern.begin();
+  kwsys_stl::string::const_iterator pattern_last = pattern.end();
+  for(kwsys_stl::string::const_iterator i = pattern_first;
+      i != pattern_last; ++i)
     {
-    int c = expr[i];
-    i = i+1;
-    if ( c == '*' )
+    int c = *i;
+    if(c == '*')
       {
-      res = res + ".*";
+      // A '*' (not between brackets) matches any string.
+      regex += ".*";
       }
-    else if ( c == '?' )
+    else if(c == '?')
       {
-      res = res + ".";
+      // A '?' (not between brackets) matches any single character.
+      regex += ".";
       }
-    else if ( c == '[' )
+    else if(c == '[')
       {
-      kwsys_stl::string::size_type j = i;
-      if ( j < n && ( expr[j] == '!' || expr[j] == '^' ) )
+      // Parse out the bracket expression.  It begins just after the
+      // opening character.
+      kwsys_stl::string::const_iterator bracket_first = i+1;
+      kwsys_stl::string::const_iterator bracket_last = bracket_first;
+
+      // The first character may be complementation '!' or '^'.
+      if(bracket_last != pattern_last &&
+         (*bracket_last == '!' || *bracket_last == '^'))
         {
-        j = j+1;
+        ++bracket_last;
         }
-      if ( j < n && expr[j] == ']' )
+
+      // If the next character is a ']' it is included in the brackets
+      // because the bracket string may not be empty.
+      if(bracket_last != pattern_last && *bracket_last == ']')
         {
-        j = j+1;
+        ++bracket_last;
         }
-      while ( j < n && expr[j] != ']' )
+
+      // Search for the closing ']'.
+      while(bracket_last != pattern_last && *bracket_last != ']')
         {
-        j = j+1;
+        ++bracket_last;
         }
-      if ( j >= n )
+
+      // Check whether we have a complete bracket string.
+      if(bracket_last == pattern_last)
         {
-        res = res + "\\[";
+        // The bracket string did not end, so it was opened simply by
+        // a '[' that is supposed to be matched literally.
+        regex += "\\[";
         }
       else
         {
-        stuff = "";
-        kwsys_stl::string::size_type cc;
-        for ( cc = i; cc < j; cc ++ )
-          {
-          if ( expr[cc] == '\\' )
-            {
-            stuff += "\\\\";
-            }
-          else
-            {
-            stuff += expr[cc];
-            }
-          }
-        i = j+1;
-        if ( stuff[0] == '!' || stuff[0] == '^' )
+        // Convert the bracket string to its regex equivalent.
+        kwsys_stl::string::const_iterator k = bracket_first;
+
+        // Open the regex block.
+        regex += "[";
+
+        // A regex range complement uses '^' instead of '!'.
+        if(k != bracket_last && *k == '!')
           {
-          stuff = '^' + stuff.substr(1);
+          regex += "^";
+          ++k;
           }
-        else if ( stuff[0] == '^' )
+
+        // Convert the remaining characters.
+        for(; k != bracket_last; ++k)
           {
-          stuff = '\\' + stuff;
+          // Backslashes must be escaped.
+          if(*k == '\\')
+            {
+            regex += "\\";
+            }
+
+          // Store this character.
+          regex += *k;
           }
-        res = res + "[" + stuff + "]";
+
+        // Close the regex block.
+        regex += "]";
+
+        // Jump to the end of the bracket string.
+        i = bracket_last;
         }
       }
     else
       {
-      char buffer[100];
-      buffer[0] = 0;
-      this->Escape(c, buffer);
-      res = res + buffer;
+      // A single character matches itself.
+      int ch = c;
+      if(!(('a' <= ch && ch <= 'z') ||
+           ('A' <= ch && ch <= 'Z') ||
+           ('0' <= ch && ch <= '9')))
+        {
+        // Escape the non-alphanumeric character.
+        regex += "\\";
+        }
+#if defined(KWSYS_GLOB_CASE_INDEPENDENT)
+      else
+        {
+        // On case-insensitive systems file names are converted to lower
+        // case before matching.
+        ch = tolower(ch);
+        }
+#endif
+
+      // Store the character.
+      regex.append(1, static_cast<char>(ch));
       }
     }
-  return res + "$";
+
+  if(require_whole_string)
+    {
+    regex += "$";
+    }
+  return regex;
 }
 
 //----------------------------------------------------------------------------
@@ -276,8 +298,8 @@ void Glob::ProcessDirectory(kwsys_stl::string::size_type start,
       realname = dir + "/" + fname;
       }
 
-#if defined( KWSYS_GLOB_CASE_INDEPENDENT )
-    // On Windows and apple, no difference between lower and upper case
+#if defined(KWSYS_GLOB_CASE_INDEPENDENT)
+    // On case-insensitive file systems convert to lower case for matching.
     fname = kwsys::SystemTools::LowerCase(fname);
 #endif
 
@@ -427,8 +449,7 @@ void Glob::AddExpression(const char* expr)
 {
   this->Internals->Expressions.push_back(
     kwsys::RegularExpression(
-      this->ConvertExpression(expr).c_str()));
-  this->Internals->TextExpressions.push_back(this->ConvertExpression(expr));
+      this->PatternToRegex(expr).c_str()));
 }
 
 //----------------------------------------------------------------------------