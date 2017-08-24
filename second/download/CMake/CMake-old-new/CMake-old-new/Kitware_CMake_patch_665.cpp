@@ -259,7 +259,7 @@ int CommandLineArguments::Parse()
           }
         else
           {
-          cerr << "Got unknown argument type: \"" << cs->VariableType << "\"" << endl;
+          kwsys_ios::cerr << "Got unknown argument type: \"" << cs->VariableType << "\"" << kwsys_ios::endl;
           return 0;
           }
         }
@@ -278,7 +278,7 @@ int CommandLineArguments::Parse()
         }
       else
         {
-        cerr << "Got unknown argument: \"" << arg.c_str() << "\"" << endl;
+        kwsys_ios::cerr << "Got unknown argument: \"" << arg.c_str() << "\"" << kwsys_ios::endl;
         return 0;
         }
       }
@@ -523,7 +523,7 @@ void CommandLineArguments::GenerateHelp()
     CommandLineArguments::Internal::SetOfStrings::iterator sit;
     for ( sit = mpit->second.begin(); sit != mpit->second.end(); sit++ )
       {
-      str << endl;
+      str << kwsys_ios::endl;
       char argument[100];
       sprintf(argument, sit->c_str());
       switch ( this->Internals->Callbacks[*sit].ArgumentType )
@@ -579,7 +579,7 @@ void CommandLineArguments::GenerateHelp()
           }
         }
       str.write(ptr, skip);
-      str << endl;
+      str << kwsys_ios::endl;
       ptr += skip;
       len -= skip;
       cnt ++;