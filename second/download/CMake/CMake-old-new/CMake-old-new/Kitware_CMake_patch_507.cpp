@@ -15,6 +15,7 @@
 #include KWSYS_HEADER(CommandLineArguments.hxx)
 
 #include KWSYS_HEADER(Configure.hxx)
+#include KWSYS_HEADER(String.hxx)
 
 #include KWSYS_HEADER(stl/vector)
 #include KWSYS_HEADER(stl/map)
@@ -44,22 +45,18 @@
 # pragma set woff 1375 /* base class destructor not virtual */
 #endif
 
+#if 0
+#  define CommandLineArguments_DEBUG(x) \
+  kwsys_ios::cout << __LINE__ << " CLA: " << x << kwsys_ios::endl
+#else
+#  define CommandLineArguments_DEBUG(x)
+#endif
+
 namespace KWSYS_NAMESPACE
 {
 
 //----------------------------------------------------------------------------
 //============================================================================
-class CommandLineArgumentsString : public kwsys_stl::string 
-{
-public:
-  typedef kwsys_stl::string StdString;
-  CommandLineArgumentsString(): StdString() {}
-  CommandLineArgumentsString(const value_type* s): StdString(s) {}
-  CommandLineArgumentsString(const value_type* s, size_type n): StdString(s, n) {}
-  CommandLineArgumentsString(const StdString& s, size_type pos=0, size_type n=npos):
-    StdString(s, pos, n) {}
-};
-
 struct CommandLineArgumentsCallbackStructure
 {
   const char* Argument;
@@ -72,11 +69,11 @@ struct CommandLineArgumentsCallbackStructure
 };
  
 class CommandLineArgumentsVectorOfStrings : 
-  public kwsys_stl::vector<CommandLineArgumentsString> {};
+  public kwsys_stl::vector<kwsys::String> {};
 class CommandLineArgumentsSetOfStrings :
-  public kwsys_stl::set<CommandLineArgumentsString> {};
+  public kwsys_stl::set<kwsys::String> {};
 class CommandLineArgumentsMapOfStrucs : 
-  public kwsys_stl::map<CommandLineArgumentsString,
+  public kwsys_stl::map<kwsys::String,
     CommandLineArgumentsCallbackStructure> {};
 
 class CommandLineArgumentsInternal
@@ -91,7 +88,7 @@ class CommandLineArgumentsInternal
 
   typedef CommandLineArgumentsVectorOfStrings VectorOfStrings;
   typedef CommandLineArgumentsMapOfStrucs CallbacksMap;
-  typedef CommandLineArgumentsString String;
+  typedef kwsys::String String;
   typedef CommandLineArgumentsSetOfStrings SetOfStrings;
 
   VectorOfStrings Argv;
@@ -153,38 +150,47 @@ void CommandLineArguments::ProcessArgument(const char* arg)
 }
 
 //----------------------------------------------------------------------------
-int CommandLineArguments::Parse()
+bool CommandLineArguments::GetMatchedArguments(
+  kwsys_stl::vector<kwsys_stl::string>* matches,
+  const kwsys_stl::string& arg)
 {
-  CommandLineArguments::Internal::VectorOfStrings::size_type cc;
-  CommandLineArguments::Internal::VectorOfStrings matches;
-  for ( cc = 0; cc < this->Internals->Argv.size(); cc ++ )
+  matches->clear();
+  CommandLineArguments::Internal::CallbacksMap::iterator it;
+
+  // Does the argument match to any we know about?
+  for ( it = this->Internals->Callbacks.begin();
+    it != this->Internals->Callbacks.end();
+    it ++ )
     {
-    this->Internals->LastArgument = cc;
-    matches.clear();
-    CommandLineArguments::Internal::String& arg = this->Internals->Argv[cc];
-    CommandLineArguments::Internal::CallbacksMap::iterator it;
-
-    // Does the argument match to any we know about?
-    for ( it = this->Internals->Callbacks.begin();
-      it != this->Internals->Callbacks.end();
-      it ++ )
+    const CommandLineArguments::Internal::String& parg = it->first;
+    CommandLineArgumentsCallbackStructure *cs = &it->second;
+    if (cs->ArgumentType == CommandLineArguments::NO_ARGUMENT ||
+      cs->ArgumentType == CommandLineArguments::SPACE_ARGUMENT) 
       {
-      const CommandLineArguments::Internal::String& parg = it->first;
-      CommandLineArgumentsCallbackStructure *cs = &it->second;
-      if (cs->ArgumentType == CommandLineArguments::NO_ARGUMENT ||
-        cs->ArgumentType == CommandLineArguments::SPACE_ARGUMENT) 
+      if ( arg == parg )
         {
-        if ( arg == parg )
-          {
-          matches.push_back(parg);
-          }
-        }
-      else if ( arg.find( parg ) == 0 )
-        {
-        matches.push_back(parg);
+        matches->push_back(parg);
         }
       }
-    if ( matches.size() > 0 )
+    else if ( arg.find( parg ) == 0 )
+      {
+      matches->push_back(parg);
+      }
+    }
+  return matches->size() > 0;
+}
+
+//----------------------------------------------------------------------------
+int CommandLineArguments::Parse()
+{
+  kwsys_stl::vector<kwsys_stl::string>::size_type cc;
+  kwsys_stl::vector<kwsys_stl::string> matches;
+  for ( cc = 0; cc < this->Internals->Argv.size(); cc ++ )
+    {
+    const kwsys_stl::string& arg = this->Internals->Argv[cc]; 
+    CommandLineArguments_DEBUG("Process argument: " << arg);
+    this->Internals->LastArgument = cc;
+    if ( this->GetMatchedArguments(&matches, arg) )
       {
       // Ok, we found one or more arguments that match what user specified.
       // Let's find the longest one.
@@ -201,112 +207,84 @@ int CommandLineArguments::Parse()
         }
       // So, the longest one is probably the right one. Now see if it has any
       // additional value
-      const char* value = 0;
       CommandLineArgumentsCallbackStructure *cs 
         = &this->Internals->Callbacks[matches[maxidx]];
       const CommandLineArguments::Internal::String& sarg = matches[maxidx];
-      if ( cs->ArgumentType == NO_ARGUMENT )
+      if ( cs->Argument != sarg )
         {
-        // No value
+        abort();
         }
-      else if ( cs->ArgumentType == SPACE_ARGUMENT )
+      switch ( cs->ArgumentType )
         {
+      case NO_ARGUMENT:
+        // No value
+        if ( !this->PopulateVariable(cs, 0) )
+          {
+          return 0;
+          }
+        break;
+      case SPACE_ARGUMENT:
         if ( cc == this->Internals->Argv.size()-1 )
           {
           this->Internals->LastArgument --;
           return 0;
           }
+        CommandLineArguments_DEBUG("This is a space argument: " << arg
+          << " value: " << this->Internals->Argv[cc+1].c_str());
         // Value is the next argument
-        value = this->Internals->Argv[cc+1].c_str();
+        if ( !this->PopulateVariable(cs, this->Internals->Argv[cc+1].c_str()) )
+          {
+          return 0;
+          }
         cc ++;
-        }
-      else if ( cs->ArgumentType == EQUAL_ARGUMENT )
-        {
+        break;
+      case EQUAL_ARGUMENT:
         if ( arg.size() == sarg.size() || *(arg.c_str() + sarg.size()) != '=' )
           {
           this->Internals->LastArgument --;
           return 0;
           }
         // Value is everythng followed the '=' sign
-        value = arg.c_str() + sarg.size()+1;
-        }
-      else if ( cs->ArgumentType == CONCAT_ARGUMENT )
-        {
-        // Value is whatever follows the argument
-        value = arg.c_str() + sarg.size();
-        }
-
-      // Call the callback
-      if ( cs->Callback )
-        {
-        if ( !cs->Callback(sarg.c_str(), value, cs->CallData) )
+        if ( !this->PopulateVariable(cs, arg.c_str() + sarg.size() + 1) )
           {
-          this->Internals->LastArgument --;
           return 0;
           }
-        }
-      if ( cs->Variable )
-        {
-        kwsys_stl::string var = "1";
-        if ( value )
-          {
-          var = value;
-          }
-        if ( cs->VariableType == CommandLineArguments::INT_TYPE )
-          {
-          int* variable = static_cast<int*>(cs->Variable);
-          char* res = 0;
-          *variable = strtol(var.c_str(), &res, 10);
-          //if ( res && *res )
-          //  {
-          //  Can handle non-int
-          //  }
-          }
-        else if ( cs->VariableType == CommandLineArguments::DOUBLE_TYPE )
-          {
-          double* variable = static_cast<double*>(cs->Variable);
-          char* res = 0;
-          *variable = strtod(var.c_str(), &res);
-          //if ( res && *res )
-          //  {
-          //  Can handle non-int
-          //  }
-          }
-        else if ( cs->VariableType == CommandLineArguments::STRING_TYPE )
-          {
-          char** variable = static_cast<char**>(cs->Variable);
-          if ( *variable )
-            {
-            delete [] *variable;
-            *variable = 0;
-            }
-          *variable = new char[ strlen(var.c_str()) + 1 ];
-          strcpy(*variable, var.c_str());
-          }
-        else if ( cs->VariableType == CommandLineArguments::STL_STRING_TYPE )
+        break;
+      case CONCAT_ARGUMENT:
+        // Value is whatever follows the argument
+        if ( !this->PopulateVariable(cs, arg.c_str() + sarg.size()) )
           {
-          kwsys_stl::string* variable = static_cast<kwsys_stl::string*>(cs->Variable);
-          *variable = var;
+          return 0;
           }
-        else if ( cs->VariableType == CommandLineArguments::BOOL_TYPE )
+        break;
+      case MULTI_ARGUMENT:
+        // Suck in all the rest of the arguments
+        CommandLineArguments_DEBUG("This is a multi argument: " << arg);
+        for (cc++; cc < this->Internals->Argv.size(); ++ cc )
           {
-          bool* variable = static_cast<bool*>(cs->Variable);
-          if ( var == "1" || var == "ON" || var == "TRUE" || var == "true" || var == "on" ||
-            var == "True" || var == "yes" || var == "Yes" || var == "YES" )
+          const kwsys_stl::string& marg = this->Internals->Argv[cc];
+          CommandLineArguments_DEBUG(" check multi argument value: " << marg);
+          if ( this->GetMatchedArguments(&matches, marg) )
             {
-            *variable = true;
+            CommandLineArguments_DEBUG("End of multi argument " << arg << " with value: " << marg);
+            break;
             }
-          else
+          CommandLineArguments_DEBUG(" populate multi argument value: " << marg);
+          if ( !this->PopulateVariable(cs, marg.c_str()) )
             {
-            *variable = false;
+            return 0;
             }
           }
-        else
+        if ( cc != this->Internals->Argv.size() )
           {
-          kwsys_ios::cerr << "Got unknown argument type: \"" << cs->VariableType << "\"" << kwsys_ios::endl;
-          this->Internals->LastArgument --;
-          return 0;
+          CommandLineArguments_DEBUG("Again End of multi argument " << arg);
+          cc--;
+          continue;
           }
+      default:
+        kwsys_ios::cerr << "Got unknown argument type: \"" << cs->ArgumentType << "\"" << kwsys_ios::endl;
+        this->Internals->LastArgument --;
+        return 0;
         }
       }
     else
@@ -404,55 +382,45 @@ void CommandLineArguments::AddArgument(const char* argument, ArgumentTypeEnum ty
 }
 
 //----------------------------------------------------------------------------
-void CommandLineArguments::AddArgument(const char* argument, ArgumentTypeEnum type,
-  int* variable, const char* help)
-{
-  this->AddArgument(argument, type, CommandLineArguments::INT_TYPE, variable, help);
-}
-
-//----------------------------------------------------------------------------
-void CommandLineArguments::AddArgument(const char* argument, ArgumentTypeEnum type,
-  double* variable, const char* help)
-{
-  this->AddArgument(argument, type, CommandLineArguments::DOUBLE_TYPE, variable, help);
-}
-
-//----------------------------------------------------------------------------
-void CommandLineArguments::AddArgument(const char* argument, ArgumentTypeEnum type,
-  char** variable, const char* help)
-{
-  this->AddArgument(argument, type, CommandLineArguments::STRING_TYPE, variable, help);
-}
-
-//----------------------------------------------------------------------------
-void CommandLineArguments::AddArgument(const char* argument, ArgumentTypeEnum type,
-  kwsys_stl::string* variable, const char* help)
-{
-  this->AddArgument(argument, type, CommandLineArguments::STL_STRING_TYPE, variable, help);
-}
-
-//----------------------------------------------------------------------------
-void CommandLineArguments::AddArgument(const char* argument, ArgumentTypeEnum type,
-  bool* variable, const char* help)
-{
-  this->AddArgument(argument, type, CommandLineArguments::BOOL_TYPE, variable, help);
-}
+#define CommandLineArgumentsAddArgumentMacro(type, ctype) \
+  void CommandLineArguments::AddArgument(const char* argument, ArgumentTypeEnum type, \
+    ctype* variable, const char* help) \
+  { \
+    this->AddArgument(argument, type, CommandLineArguments::type##_TYPE, variable, help); \
+  }
+
+CommandLineArgumentsAddArgumentMacro(BOOL,       bool);
+CommandLineArgumentsAddArgumentMacro(INT,        int);
+CommandLineArgumentsAddArgumentMacro(DOUBLE,     double);
+CommandLineArgumentsAddArgumentMacro(STRING,     char*);
+CommandLineArgumentsAddArgumentMacro(STL_STRING, kwsys_stl::string);
+
+CommandLineArgumentsAddArgumentMacro(VECTOR_BOOL,       kwsys_stl::vector<bool>);
+CommandLineArgumentsAddArgumentMacro(VECTOR_INT,        kwsys_stl::vector<int>);
+CommandLineArgumentsAddArgumentMacro(VECTOR_DOUBLE,     kwsys_stl::vector<double>);
+CommandLineArgumentsAddArgumentMacro(VECTOR_STRING,     kwsys_stl::vector<char*>);
+CommandLineArgumentsAddArgumentMacro(VECTOR_STL_STRING, kwsys_stl::vector<kwsys_stl::string>);
 
 //----------------------------------------------------------------------------
-void CommandLineArguments::AddBooleanArgument(const char* argument, bool*
-  variable, const char* help)
-{
-  this->AddArgument(argument, CommandLineArguments::NO_ARGUMENT,
-    CommandLineArguments::BOOL_TYPE, variable, help);
-}
-
-//----------------------------------------------------------------------------
-void CommandLineArguments::AddBooleanArgument(const char* argument, int*
-  variable, const char* help)
-{
-  this->AddArgument(argument, CommandLineArguments::NO_ARGUMENT,
-    CommandLineArguments::INT_TYPE, variable, help);
-}
+#define CommandLineArgumentsAddBooleanArgumentMacro(type, ctype) \
+  void CommandLineArguments::AddBooleanArgument(const char* argument, \
+    ctype* variable, const char* help) \
+  { \
+    this->AddArgument(argument, CommandLineArguments::NO_ARGUMENT, \
+      CommandLineArguments::type##_TYPE, variable, help); \
+  }
+
+CommandLineArgumentsAddBooleanArgumentMacro(BOOL,       bool);
+CommandLineArgumentsAddBooleanArgumentMacro(INT,        int);
+CommandLineArgumentsAddBooleanArgumentMacro(DOUBLE,     double);
+CommandLineArgumentsAddBooleanArgumentMacro(STRING,     char*);
+CommandLineArgumentsAddBooleanArgumentMacro(STL_STRING, kwsys_stl::string);
+
+CommandLineArgumentsAddBooleanArgumentMacro(VECTOR_BOOL,       kwsys_stl::vector<bool>);
+CommandLineArgumentsAddBooleanArgumentMacro(VECTOR_INT,        kwsys_stl::vector<int>);
+CommandLineArgumentsAddBooleanArgumentMacro(VECTOR_DOUBLE,     kwsys_stl::vector<double>);
+CommandLineArgumentsAddBooleanArgumentMacro(VECTOR_STRING,     kwsys_stl::vector<char*>);
+CommandLineArgumentsAddBooleanArgumentMacro(VECTOR_STL_STRING, kwsys_stl::vector<kwsys_stl::string>);
 
 //----------------------------------------------------------------------------
 void CommandLineArguments::SetClientData(void* client_data)
@@ -614,6 +582,7 @@ void CommandLineArguments::GenerateHelp()
         case CommandLineArguments::CONCAT_ARGUMENT: strcat(argument, "opt"); break;
         case CommandLineArguments::SPACE_ARGUMENT:  strcat(argument, " opt"); break;
         case CommandLineArguments::EQUAL_ARGUMENT:  strcat(argument, "=opt"); break;
+        case CommandLineArguments::MULTI_ARGUMENT:  strcat(argument, " opt opt ..."); break;
         }
       char buffer[80];
       sprintf(buffer, format, argument);
@@ -678,4 +647,181 @@ void CommandLineArguments::GenerateHelp()
   this->Help = str.str();
 }
 
+//----------------------------------------------------------------------------
+void CommandLineArguments::PopulateVariable(
+  bool* variable, const kwsys_stl::string& value)
+{
+  if ( value == "1" || value == "ON" || value == "on" || value == "On" ||
+    value == "TRUE" || value == "true" || value == "True" ||
+    value == "yes" || value == "Yes" || value == "YES" )
+    {
+    *variable = true;
+    }
+  else
+    {
+    *variable = false;
+    }
+}
+
+//----------------------------------------------------------------------------
+void CommandLineArguments::PopulateVariable(
+  int* variable, const kwsys_stl::string& value)
+{
+  char* res = 0;
+  *variable = strtol(value.c_str(), &res, 10);
+  //if ( res && *res )
+  //  {
+  //  Can handle non-int
+  //  }
+}
+
+//----------------------------------------------------------------------------
+void CommandLineArguments::PopulateVariable(
+  double* variable, const kwsys_stl::string& value)
+{
+  char* res = 0;
+  *variable = strtod(value.c_str(), &res);
+  //if ( res && *res )
+  //  {
+  //  Can handle non-double
+  //  }
+}
+
+//----------------------------------------------------------------------------
+void CommandLineArguments::PopulateVariable(
+  char** variable, const kwsys_stl::string& value)
+{
+  if ( *variable )
+    {
+    delete [] *variable;
+    *variable = 0;
+    }
+  *variable = new char[ value.size() + 1 ];
+  strcpy(*variable, value.c_str());
+}
+
+//----------------------------------------------------------------------------
+void CommandLineArguments::PopulateVariable(
+  kwsys_stl::string* variable, const kwsys_stl::string& value)
+{
+  *variable = value;
+}
+
+//----------------------------------------------------------------------------
+void CommandLineArguments::PopulateVariable(
+  kwsys_stl::vector<bool>* variable, const kwsys_stl::string& value)
+{
+  bool val = false;
+  if ( value == "1" || value == "ON" || value == "on" || value == "On" ||
+    value == "TRUE" || value == "true" || value == "True" ||
+    value == "yes" || value == "Yes" || value == "YES" )
+    {
+    val = true;
+    }
+  variable->push_back(val);
+}
+
+//----------------------------------------------------------------------------
+void CommandLineArguments::PopulateVariable(
+  kwsys_stl::vector<int>* variable, const kwsys_stl::string& value)
+{
+  char* res = 0;
+  variable->push_back(strtol(value.c_str(), &res, 10));
+  //if ( res && *res )
+  //  {
+  //  Can handle non-int
+  //  }
+}
+
+//----------------------------------------------------------------------------
+void CommandLineArguments::PopulateVariable(
+  kwsys_stl::vector<double>* variable, const kwsys_stl::string& value)
+{
+  char* res = 0;
+  variable->push_back(strtod(value.c_str(), &res));
+  //if ( res && *res )
+  //  {
+  //  Can handle non-int
+  //  }
+}
+
+//----------------------------------------------------------------------------
+void CommandLineArguments::PopulateVariable(
+  kwsys_stl::vector<char*>* variable, const kwsys_stl::string& value)
+{
+  char* var = new char[ value.size() + 1 ];
+  strcpy(var, value.c_str());
+  variable->push_back(var);
+}
+
+//----------------------------------------------------------------------------
+void CommandLineArguments::PopulateVariable(
+  kwsys_stl::vector<kwsys_stl::string>* variable,
+  const kwsys_stl::string& value)
+{
+  variable->push_back(value);
+}
+
+//----------------------------------------------------------------------------
+bool CommandLineArguments::PopulateVariable(CommandLineArgumentsCallbackStructure* cs,
+  const char* value)
+{
+  // Call the callback
+  if ( cs->Callback )
+    {
+    if ( !cs->Callback(cs->Argument, value, cs->CallData) )
+      {
+      this->Internals->LastArgument --;
+      return 0;
+      }
+    }
+  if ( cs->Variable )
+    {
+    kwsys_stl::string var = "1";
+    if ( value )
+      {
+      var = value;
+      }
+    switch ( cs->VariableType )
+      {
+    case CommandLineArguments::INT_TYPE:
+      this->PopulateVariable(static_cast<int*>(cs->Variable), var);
+      break;
+    case CommandLineArguments::DOUBLE_TYPE:
+      this->PopulateVariable(static_cast<double*>(cs->Variable), var);
+      break;
+    case CommandLineArguments::STRING_TYPE:
+      this->PopulateVariable(static_cast<char**>(cs->Variable), var);
+      break;
+    case CommandLineArguments::STL_STRING_TYPE:
+      this->PopulateVariable(static_cast<kwsys_stl::string*>(cs->Variable), var);
+      break;
+    case CommandLineArguments::BOOL_TYPE:
+      this->PopulateVariable(static_cast<bool*>(cs->Variable), var);
+      break;
+    case CommandLineArguments::VECTOR_BOOL_TYPE:
+      this->PopulateVariable(static_cast<kwsys_stl::vector<bool>*>(cs->Variable), var);
+      break;
+    case CommandLineArguments::VECTOR_INT_TYPE:
+      this->PopulateVariable(static_cast<kwsys_stl::vector<int>*>(cs->Variable), var);
+      break;
+    case CommandLineArguments::VECTOR_DOUBLE_TYPE:
+      this->PopulateVariable(static_cast<kwsys_stl::vector<double>*>(cs->Variable), var);
+      break;
+    case CommandLineArguments::VECTOR_STRING_TYPE:
+      this->PopulateVariable(static_cast<kwsys_stl::vector<char*>*>(cs->Variable), var);
+      break;
+    case CommandLineArguments::VECTOR_STL_STRING_TYPE:
+      this->PopulateVariable(static_cast<kwsys_stl::vector<kwsys_stl::string>*>(cs->Variable), var);
+      break;
+    default:
+      kwsys_ios::cerr << "Got unknown variable type: \"" << cs->VariableType << "\"" << kwsys_ios::endl;
+      this->Internals->LastArgument --;
+      return 0;
+      }
+    }
+  return 1;
+}
+
+
 } // namespace KWSYS_NAMESPACE