@@ -15,22 +15,19 @@
 #include KWSYS_HEADER(Configure.hxx)
 #include KWSYS_HEADER(String.hxx)
 
-#include KWSYS_HEADER(stl/vector)
-#include KWSYS_HEADER(stl/map)
-#include KWSYS_HEADER(stl/set)
-#include KWSYS_HEADER(ios/sstream)
-#include KWSYS_HEADER(ios/iostream)
-
 // Work-around CMake dependency scanning limitation.  This must
 // duplicate the above list of headers.
 #if 0
 # include "CommandLineArguments.hxx.in"
 # include "Configure.hxx.in"
-# include "kwsys_stl.hxx.in"
-# include "kwsys_ios_sstream.h.in"
-# include "kwsys_ios_iostream.h.in"
 #endif
 
+#include <vector>
+#include <map>
+#include <set>
+#include <sstream>
+#include <iostream>
+
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
@@ -45,7 +42,7 @@
 
 #if 0
 #  define CommandLineArguments_DEBUG(x) \
-  kwsys_ios::cout << __LINE__ << " CLA: " << x << kwsys_ios::endl
+  std::cout << __LINE__ << " CLA: " << x << std::endl
 #else
 #  define CommandLineArguments_DEBUG(x)
 #endif
@@ -67,11 +64,11 @@ struct CommandLineArgumentsCallbackStructure
 };
  
 class CommandLineArgumentsVectorOfStrings : 
-  public kwsys_stl::vector<kwsys::String> {};
+  public std::vector<kwsys::String> {};
 class CommandLineArgumentsSetOfStrings :
-  public kwsys_stl::set<kwsys::String> {};
+  public std::set<kwsys::String> {};
 class CommandLineArgumentsMapOfStrucs : 
-  public kwsys_stl::map<kwsys::String,
+  public std::map<kwsys::String,
     CommandLineArgumentsCallbackStructure> {};
 
 class CommandLineArgumentsInternal
@@ -152,8 +149,8 @@ void CommandLineArguments::ProcessArgument(const char* arg)
 
 //----------------------------------------------------------------------------
 bool CommandLineArguments::GetMatchedArguments(
-  kwsys_stl::vector<kwsys_stl::string>* matches,
-  const kwsys_stl::string& arg)
+  std::vector<std::string>* matches,
+  const std::string& arg)
 {
   matches->clear();
   CommandLineArguments::Internal::CallbacksMap::iterator it;
@@ -184,15 +181,15 @@ bool CommandLineArguments::GetMatchedArguments(
 //----------------------------------------------------------------------------
 int CommandLineArguments::Parse()
 {
-  kwsys_stl::vector<kwsys_stl::string>::size_type cc;
-  kwsys_stl::vector<kwsys_stl::string> matches;
+  std::vector<std::string>::size_type cc;
+  std::vector<std::string> matches;
   if ( this->StoreUnusedArgumentsFlag )
     {
     this->Internals->UnusedArguments.clear();
     }
   for ( cc = 0; cc < this->Internals->Argv.size(); cc ++ )
     {
-    const kwsys_stl::string& arg = this->Internals->Argv[cc]; 
+    const std::string& arg = this->Internals->Argv[cc];
     CommandLineArguments_DEBUG("Process argument: " << arg);
     this->Internals->LastArgument = cc;
     if ( this->GetMatchedArguments(&matches, arg) )
@@ -214,7 +211,7 @@ int CommandLineArguments::Parse()
       // additional value
       CommandLineArgumentsCallbackStructure *cs 
         = &this->Internals->Callbacks[matches[maxidx]];
-      const kwsys_stl::string& sarg = matches[maxidx];
+      const std::string& sarg = matches[maxidx];
       if ( cs->Argument != sarg )
         {
         abort();
@@ -267,7 +264,7 @@ int CommandLineArguments::Parse()
         CommandLineArguments_DEBUG("This is a multi argument: " << arg);
         for (cc++; cc < this->Internals->Argv.size(); ++ cc )
           {
-          const kwsys_stl::string& marg = this->Internals->Argv[cc];
+          const std::string& marg = this->Internals->Argv[cc];
           CommandLineArguments_DEBUG(" check multi argument value: " << marg);
           if ( this->GetMatchedArguments(&matches, marg) )
             {
@@ -288,7 +285,7 @@ int CommandLineArguments::Parse()
           }
         break;
       default:
-        kwsys_ios::cerr << "Got unknown argument type: \"" << cs->ArgumentType << "\"" << kwsys_ios::endl;
+        std::cerr << "Got unknown argument type: \"" << cs->ArgumentType << "\"" << std::endl;
         this->Internals->LastArgument --;
         return 0;
         }
@@ -313,7 +310,7 @@ int CommandLineArguments::Parse()
         }
       else
         {
-        kwsys_ios::cerr << "Got unknown argument: \"" << arg << "\"" << kwsys_ios::endl;
+        std::cerr << "Got unknown argument: \"" << arg << "\"" << std::endl;
         this->Internals->LastArgument --;
         return 0;
         }
@@ -430,13 +427,13 @@ CommandLineArgumentsAddArgumentMacro(BOOL,       bool)
 CommandLineArgumentsAddArgumentMacro(INT,        int)
 CommandLineArgumentsAddArgumentMacro(DOUBLE,     double)
 CommandLineArgumentsAddArgumentMacro(STRING,     char*)
-CommandLineArgumentsAddArgumentMacro(STL_STRING, kwsys_stl::string)
+CommandLineArgumentsAddArgumentMacro(STL_STRING, std::string)
 
-CommandLineArgumentsAddArgumentMacro(VECTOR_BOOL,       kwsys_stl::vector<bool>)
-CommandLineArgumentsAddArgumentMacro(VECTOR_INT,        kwsys_stl::vector<int>)
-CommandLineArgumentsAddArgumentMacro(VECTOR_DOUBLE,     kwsys_stl::vector<double>)
-CommandLineArgumentsAddArgumentMacro(VECTOR_STRING,     kwsys_stl::vector<char*>)
-CommandLineArgumentsAddArgumentMacro(VECTOR_STL_STRING, kwsys_stl::vector<kwsys_stl::string>)
+CommandLineArgumentsAddArgumentMacro(VECTOR_BOOL,       std::vector<bool>)
+CommandLineArgumentsAddArgumentMacro(VECTOR_INT,        std::vector<int>)
+CommandLineArgumentsAddArgumentMacro(VECTOR_DOUBLE,     std::vector<double>)
+CommandLineArgumentsAddArgumentMacro(VECTOR_STRING,     std::vector<char*>)
+CommandLineArgumentsAddArgumentMacro(VECTOR_STL_STRING, std::vector<std::string>)
 
 //----------------------------------------------------------------------------
 #define CommandLineArgumentsAddBooleanArgumentMacro(type, ctype) \
@@ -451,7 +448,7 @@ CommandLineArgumentsAddBooleanArgumentMacro(BOOL,       bool)
 CommandLineArgumentsAddBooleanArgumentMacro(INT,        int)
 CommandLineArgumentsAddBooleanArgumentMacro(DOUBLE,     double)
 CommandLineArgumentsAddBooleanArgumentMacro(STRING,     char*)
-CommandLineArgumentsAddBooleanArgumentMacro(STL_STRING, kwsys_stl::string)
+CommandLineArgumentsAddBooleanArgumentMacro(STL_STRING, std::string)
 
 //----------------------------------------------------------------------------
 void CommandLineArguments::SetClientData(void* client_data)
@@ -518,12 +515,12 @@ unsigned int CommandLineArguments::GetLastArgument()
 //----------------------------------------------------------------------------
 void CommandLineArguments::GenerateHelp()
 {
-  kwsys_ios::ostringstream str;
+  std::ostringstream str;
   
   // Collapse all arguments into the map of vectors of all arguments that do
   // the same thing.
   CommandLineArguments::Internal::CallbacksMap::iterator it;
-  typedef kwsys_stl::map<CommandLineArguments::Internal::String, 
+  typedef std::map<CommandLineArguments::Internal::String,
      CommandLineArguments::Internal::SetOfStrings > MapArgs;
   MapArgs mp;
   MapArgs::iterator mpit, smpit;
@@ -604,7 +601,7 @@ void CommandLineArguments::GenerateHelp()
     CommandLineArguments::Internal::SetOfStrings::iterator sit;
     for ( sit = mpit->second.begin(); sit != mpit->second.end(); sit++ )
       {
-      str << kwsys_ios::endl;
+      str << std::endl;
       char argument[100];
       sprintf(argument, "%s", sit->c_str());
       switch ( this->Internals->Callbacks[*sit].ArgumentType )
@@ -658,8 +655,8 @@ void CommandLineArguments::GenerateHelp()
           skip = cc;
           }
         }
-      str.write(ptr, static_cast<kwsys_ios::streamsize>(skip));
-      str << kwsys_ios::endl;
+      str.write(ptr, static_cast<std::streamsize>(skip));
+      str << std::endl;
       ptr += skip;
       len -= skip;
       cnt ++;
@@ -680,7 +677,7 @@ void CommandLineArguments::GenerateHelp()
 
 //----------------------------------------------------------------------------
 void CommandLineArguments::PopulateVariable(
-  bool* variable, const kwsys_stl::string& value)
+  bool* variable, const std::string& value)
 {
   if ( value == "1" || value == "ON" || value == "on" || value == "On" ||
     value == "TRUE" || value == "true" || value == "True" ||
@@ -696,7 +693,7 @@ void CommandLineArguments::PopulateVariable(
 
 //----------------------------------------------------------------------------
 void CommandLineArguments::PopulateVariable(
-  int* variable, const kwsys_stl::string& value)
+  int* variable, const std::string& value)
 {
   char* res = 0;
   *variable = static_cast<int>(strtol(value.c_str(), &res, 10));
@@ -708,7 +705,7 @@ void CommandLineArguments::PopulateVariable(
 
 //----------------------------------------------------------------------------
 void CommandLineArguments::PopulateVariable(
-  double* variable, const kwsys_stl::string& value)
+  double* variable, const std::string& value)
 {
   char* res = 0;
   *variable = strtod(value.c_str(), &res);
@@ -720,7 +717,7 @@ void CommandLineArguments::PopulateVariable(
 
 //----------------------------------------------------------------------------
 void CommandLineArguments::PopulateVariable(
-  char** variable, const kwsys_stl::string& value)
+  char** variable, const std::string& value)
 {
   if ( *variable )
     {
@@ -733,14 +730,14 @@ void CommandLineArguments::PopulateVariable(
 
 //----------------------------------------------------------------------------
 void CommandLineArguments::PopulateVariable(
-  kwsys_stl::string* variable, const kwsys_stl::string& value)
+  std::string* variable, const std::string& value)
 {
   *variable = value;
 }
 
 //----------------------------------------------------------------------------
 void CommandLineArguments::PopulateVariable(
-  kwsys_stl::vector<bool>* variable, const kwsys_stl::string& value)
+  std::vector<bool>* variable, const std::string& value)
 {
   bool val = false;
   if ( value == "1" || value == "ON" || value == "on" || value == "On" ||
@@ -754,7 +751,7 @@ void CommandLineArguments::PopulateVariable(
 
 //----------------------------------------------------------------------------
 void CommandLineArguments::PopulateVariable(
-  kwsys_stl::vector<int>* variable, const kwsys_stl::string& value)
+  std::vector<int>* variable, const std::string& value)
 {
   char* res = 0;
   variable->push_back(static_cast<int>(strtol(value.c_str(), &res, 10)));
@@ -766,7 +763,7 @@ void CommandLineArguments::PopulateVariable(
 
 //----------------------------------------------------------------------------
 void CommandLineArguments::PopulateVariable(
-  kwsys_stl::vector<double>* variable, const kwsys_stl::string& value)
+  std::vector<double>* variable, const std::string& value)
 {
   char* res = 0;
   variable->push_back(strtod(value.c_str(), &res));
@@ -778,7 +775,7 @@ void CommandLineArguments::PopulateVariable(
 
 //----------------------------------------------------------------------------
 void CommandLineArguments::PopulateVariable(
-  kwsys_stl::vector<char*>* variable, const kwsys_stl::string& value)
+  std::vector<char*>* variable, const std::string& value)
 {
   char* var = new char[ value.size() + 1 ];
   strcpy(var, value.c_str());
@@ -787,8 +784,8 @@ void CommandLineArguments::PopulateVariable(
 
 //----------------------------------------------------------------------------
 void CommandLineArguments::PopulateVariable(
-  kwsys_stl::vector<kwsys_stl::string>* variable,
-  const kwsys_stl::string& value)
+  std::vector<std::string>* variable,
+  const std::string& value)
 {
   variable->push_back(value);
 }
@@ -809,7 +806,7 @@ bool CommandLineArguments::PopulateVariable(CommandLineArgumentsCallbackStructur
   CommandLineArguments_DEBUG("Set argument: " << cs->Argument << " to " << value);
   if ( cs->Variable )
     {
-    kwsys_stl::string var = "1";
+    std::string var = "1";
     if ( value )
       {
       var = value;
@@ -826,28 +823,28 @@ bool CommandLineArguments::PopulateVariable(CommandLineArgumentsCallbackStructur
       this->PopulateVariable(static_cast<char**>(cs->Variable), var);
       break;
     case CommandLineArguments::STL_STRING_TYPE:
-      this->PopulateVariable(static_cast<kwsys_stl::string*>(cs->Variable), var);
+      this->PopulateVariable(static_cast<std::string*>(cs->Variable), var);
       break;
     case CommandLineArguments::BOOL_TYPE:
       this->PopulateVariable(static_cast<bool*>(cs->Variable), var);
       break;
     case CommandLineArguments::VECTOR_BOOL_TYPE:
-      this->PopulateVariable(static_cast<kwsys_stl::vector<bool>*>(cs->Variable), var);
+      this->PopulateVariable(static_cast<std::vector<bool>*>(cs->Variable), var);
       break;
     case CommandLineArguments::VECTOR_INT_TYPE:
-      this->PopulateVariable(static_cast<kwsys_stl::vector<int>*>(cs->Variable), var);
+      this->PopulateVariable(static_cast<std::vector<int>*>(cs->Variable), var);
       break;
     case CommandLineArguments::VECTOR_DOUBLE_TYPE:
-      this->PopulateVariable(static_cast<kwsys_stl::vector<double>*>(cs->Variable), var);
+      this->PopulateVariable(static_cast<std::vector<double>*>(cs->Variable), var);
       break;
     case CommandLineArguments::VECTOR_STRING_TYPE:
-      this->PopulateVariable(static_cast<kwsys_stl::vector<char*>*>(cs->Variable), var);
+      this->PopulateVariable(static_cast<std::vector<char*>*>(cs->Variable), var);
       break;
     case CommandLineArguments::VECTOR_STL_STRING_TYPE:
-      this->PopulateVariable(static_cast<kwsys_stl::vector<kwsys_stl::string>*>(cs->Variable), var);
+      this->PopulateVariable(static_cast<std::vector<std::string>*>(cs->Variable), var);
       break;
     default:
-      kwsys_ios::cerr << "Got unknown variable type: \"" << cs->VariableType << "\"" << kwsys_ios::endl;
+      std::cerr << "Got unknown variable type: \"" << cs->VariableType << "\"" << std::endl;
       this->Internals->LastArgument --;
       return 0;
       }