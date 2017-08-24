@@ -465,6 +465,17 @@ const char* CommandLineArguments::GetHelp(const char* arg)
 }
 
 //----------------------------------------------------------------------------
+void CommandLineArguments::SetLineLength(unsigned int ll)
+{
+  if ( ll < 9 || ll > 1000 )
+    {
+    return;
+    }
+  this->LineLength = ll;
+  this->GenerateHelp();
+}
+
+//----------------------------------------------------------------------------
 void CommandLineArguments::GenerateHelp()
 {
   kwsys_ios::ostringstream str;
@@ -528,9 +539,9 @@ void CommandLineArguments::GenerateHelp()
       switch ( this->Internals->Callbacks[*sit].ArgumentType )
         {
         case CommandLineArguments::NO_ARGUMENT:     clen += 0; break;
-        case CommandLineArguments::CONCAT_ARGUMENT: clen += 6; break;
-        case CommandLineArguments::SPACE_ARGUMENT:  clen += 7; break;
-        case CommandLineArguments::EQUAL_ARGUMENT:  clen += 7; break;
+        case CommandLineArguments::CONCAT_ARGUMENT: clen += 3; break;
+        case CommandLineArguments::SPACE_ARGUMENT:  clen += 4; break;
+        case CommandLineArguments::EQUAL_ARGUMENT:  clen += 4; break;
         }
       if ( clen > maxlen )
         {
@@ -539,9 +550,11 @@ void CommandLineArguments::GenerateHelp()
       }
     }
 
+  maxlen += 2; // For the space after option
+
   // Create format for that string
   char format[80];
-  sprintf(format, "%%%ds", static_cast<unsigned int>(maxlen));
+  sprintf(format, "%%%ds  ", static_cast<unsigned int>(maxlen-2));
 
 
   // Print help for each option
@@ -558,15 +571,14 @@ void CommandLineArguments::GenerateHelp()
       switch ( this->Internals->Callbacks[*sit].ArgumentType )
         {
         case CommandLineArguments::NO_ARGUMENT: break;
-        case CommandLineArguments::CONCAT_ARGUMENT: strcat(argument, "option"); break;
-        case CommandLineArguments::SPACE_ARGUMENT:  strcat(argument, " option"); break;
-        case CommandLineArguments::EQUAL_ARGUMENT:  strcat(argument, "=option"); break;
+        case CommandLineArguments::CONCAT_ARGUMENT: strcat(argument, "opt"); break;
+        case CommandLineArguments::SPACE_ARGUMENT:  strcat(argument, " opt"); break;
+        case CommandLineArguments::EQUAL_ARGUMENT:  strcat(argument, "=opt"); break;
         }
       char buffer[80];
       sprintf(buffer, format, argument);
       str << buffer;
       }
-    str << "\t";
     const char* ptr = this->Internals->Callbacks[mpit->first].Help;
     int len = strlen(ptr);
     int cnt = 0;
@@ -589,7 +601,6 @@ void CommandLineArguments::GenerateHelp()
           {
           str << " ";
           }
-        str << "\t";
         }
       CommandLineArguments::Internal::String::size_type skip = len;
       if ( skip > this->LineLength - maxlen )
@@ -614,6 +625,16 @@ void CommandLineArguments::GenerateHelp()
       cnt ++;
       }
     }
+  /*
+  // This can help debugging help string
+  str << endl;
+  unsigned int cc;
+  for ( cc = 0; cc < this->LineLength; cc ++ )
+    {
+    str << cc % 10;
+    }
+  str << endl;
+  */
   this->Help = str.str();
 }
 