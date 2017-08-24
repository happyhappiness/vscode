@@ -103,7 +103,7 @@ ::InitialPass(std::vector<std::string> const& args, cmExecutionStatus &)
     }
 
   std::string e = "does not recognize sub-command "+subCommand;
-  this->SetError(e.c_str());
+  this->SetError(e);
   return false;
 }
 
@@ -115,15 +115,15 @@ bool cmStringCommand::HandleHashCommand(std::vector<std::string> const& args)
     {
     cmOStringStream e;
     e << args[0] << " requires an output variable and an input string";
-    this->SetError(e.str().c_str());
+    this->SetError(e.str());
     return false;
     }
 
   cmsys::auto_ptr<cmCryptoHash> hash(cmCryptoHash::New(args[0].c_str()));
   if(hash.get())
     {
-    std::string out = hash->HashString(args[2].c_str());
-    this->Makefile->AddDefinition(args[1].c_str(), out.c_str());
+    std::string out = hash->HashString(args[2]);
+    this->Makefile->AddDefinition(args[1], out.c_str());
     return true;
     }
   return false;
@@ -158,7 +158,7 @@ bool cmStringCommand::HandleToUpperLowerCommand(
     }
 
   // Store the output in the provided variable.
-  this->Makefile->AddDefinition(outvar.c_str(), output.c_str());
+  this->Makefile->AddDefinition(outvar, output.c_str());
   return true;
 }
 
@@ -185,12 +185,12 @@ bool cmStringCommand::HandleAsciiCommand(std::vector<std::string> const& args)
       std::string error = "Character with code ";
       error += args[cc];
       error += " does not exist.";
-      this->SetError(error.c_str());
+      this->SetError(error);
       return false;
       }
     }
   // Store the output in the provided variable.
-  this->Makefile->AddDefinition(outvar.c_str(), output.c_str());
+  this->Makefile->AddDefinition(outvar, output.c_str());
   return true;
 }
 
@@ -226,7 +226,7 @@ bool cmStringCommand::HandleConfigureCommand(
       {
       cmOStringStream err;
       err << "Unrecognized argument \"" << args[i] << "\"";
-      this->SetError(err.str().c_str());
+      this->SetError(err.str());
       return false;
       }
     }
@@ -236,7 +236,7 @@ bool cmStringCommand::HandleConfigureCommand(
   this->Makefile->ConfigureString(args[1], output, atOnly, escapeQuotes);
 
   // Store the output in the provided variable.
-  this->Makefile->AddDefinition(args[2].c_str(), output.c_str());
+  this->Makefile->AddDefinition(args[2], output.c_str());
 
   return true;
 }
@@ -282,7 +282,7 @@ bool cmStringCommand::HandleRegexCommand(std::vector<std::string> const& args)
     }
 
   std::string e = "sub-command REGEX does not recognize mode "+mode;
-  this->SetError(e.c_str());
+  this->SetError(e);
   return false;
 }
 
@@ -308,7 +308,7 @@ bool cmStringCommand::RegexMatch(std::vector<std::string> const& args)
     {
     std::string e =
       "sub-command REGEX, mode MATCH failed to compile regex \""+regex+"\".";
-    this->SetError(e.c_str());
+    this->SetError(e);
     return false;
     }
 
@@ -324,14 +324,14 @@ bool cmStringCommand::RegexMatch(std::vector<std::string> const& args)
       std::string e =
         "sub-command REGEX, mode MATCH regex \""+regex+
         "\" matched an empty string.";
-      this->SetError(e.c_str());
+      this->SetError(e);
       return false;
       }
     output = input.substr(l, r-l);
     }
 
   // Store the output in the provided variable.
-  this->Makefile->AddDefinition(outvar.c_str(), output.c_str());
+  this->Makefile->AddDefinition(outvar, output.c_str());
   return true;
 }
 
@@ -358,7 +358,7 @@ bool cmStringCommand::RegexMatchAll(std::vector<std::string> const& args)
     std::string e =
       "sub-command REGEX, mode MATCHALL failed to compile regex \""+
       regex+"\".";
-    this->SetError(e.c_str());
+    this->SetError(e);
     return false;
     }
 
@@ -374,7 +374,7 @@ bool cmStringCommand::RegexMatchAll(std::vector<std::string> const& args)
       {
       std::string e = "sub-command REGEX, mode MATCHALL regex \""+
         regex+"\" matched an empty string.";
-      this->SetError(e.c_str());
+      this->SetError(e);
       return false;
       }
     if(output.length() > 0)
@@ -386,7 +386,7 @@ bool cmStringCommand::RegexMatchAll(std::vector<std::string> const& args)
     }
 
   // Store the output in the provided variable.
-  this->Makefile->AddDefinition(outvar.c_str(), output.c_str());
+  this->Makefile->AddDefinition(outvar, output.c_str());
   return true;
 }
 
@@ -439,7 +439,7 @@ bool cmStringCommand::RegexReplace(std::vector<std::string> const& args)
         std::string e = "sub-command REGEX, mode REPLACE: Unknown escape \"";
         e += replace.substr(r, 2);
         e += "\" in replace-expression.";
-        this->SetError(e.c_str());
+        this->SetError(e);
         return false;
         }
       r += 2;
@@ -462,7 +462,7 @@ bool cmStringCommand::RegexReplace(std::vector<std::string> const& args)
     std::string e =
       "sub-command REGEX, mode REPLACE failed to compile regex \""+
       regex+"\".";
-    this->SetError(e.c_str());
+    this->SetError(e);
     return false;
     }
 
@@ -483,7 +483,7 @@ bool cmStringCommand::RegexReplace(std::vector<std::string> const& args)
       {
       std::string e = "sub-command REGEX, mode REPLACE regex \""+
         regex+"\" matched an empty string.";
-      this->SetError(e.c_str());
+      this->SetError(e);
       return false;
       }
 
@@ -513,7 +513,7 @@ bool cmStringCommand::RegexReplace(std::vector<std::string> const& args)
             "sub-command REGEX, mode REPLACE: replace expression \""+
             replace+"\" contains an out-of-range escape for regex \""+
             regex+"\".";
-          this->SetError(e.c_str());
+          this->SetError(e);
           return false;
           }
         }
@@ -527,7 +527,7 @@ bool cmStringCommand::RegexReplace(std::vector<std::string> const& args)
   output += input.substr(base, input.length()-base);
 
   // Store the output in the provided variable.
-  this->Makefile->AddDefinition(outvar.c_str(), output.c_str());
+  this->Makefile->AddDefinition(outvar, output.c_str());
   return true;
 }
 
@@ -616,12 +616,12 @@ bool cmStringCommand::HandleFindCommand(std::vector<std::string> const&
     {
     cmOStringStream s;
     s << pos;
-    this->Makefile->AddDefinition(outvar.c_str(), s.str().c_str());
+    this->Makefile->AddDefinition(outvar, s.str().c_str());
     return true;
     }
 
   // the character was not found, but this is not really an error
-  this->Makefile->AddDefinition(outvar.c_str(), "-1");
+  this->Makefile->AddDefinition(outvar, "-1");
   return true;
 }
 
@@ -643,7 +643,7 @@ bool cmStringCommand::HandleCompareCommand(std::vector<std::string> const&
       std::string e = "sub-command COMPARE, mode ";
       e += mode;
       e += " needs at least 5 arguments total to command.";
-      this->SetError(e.c_str());
+      this->SetError(e);
       return false;
       }
 
@@ -669,16 +669,16 @@ bool cmStringCommand::HandleCompareCommand(std::vector<std::string> const&
       }
     if(result)
       {
-      this->Makefile->AddDefinition(outvar.c_str(), "1");
+      this->Makefile->AddDefinition(outvar, "1");
       }
     else
       {
-      this->Makefile->AddDefinition(outvar.c_str(), "0");
+      this->Makefile->AddDefinition(outvar, "0");
       }
     return true;
     }
   std::string e = "sub-command COMPARE does not recognize mode "+mode;
-  this->SetError(e.c_str());
+  this->SetError(e);
   return false;
 }
 
@@ -705,7 +705,7 @@ bool cmStringCommand::HandleReplaceCommand(std::vector<std::string> const&
   cmsys::SystemTools::ReplaceString(input, matchExpression.c_str(),
                                     replaceExpression.c_str());
 
-  this->Makefile->AddDefinition(variableName.c_str(), input.c_str());
+  this->Makefile->AddDefinition(variableName, input.c_str());
   return true;
 }
 
@@ -731,7 +731,7 @@ bool cmStringCommand::HandleSubstringCommand(std::vector<std::string> const&
     cmOStringStream ostr;
     ostr << "begin index: " << begin << " is out of range 0 - "
          << stringLength;
-    this->SetError(ostr.str().c_str());
+    this->SetError(ostr.str());
     return false;
     }
   int leftOverLength = intStringLength - begin;
@@ -740,11 +740,11 @@ bool cmStringCommand::HandleSubstringCommand(std::vector<std::string> const&
     cmOStringStream ostr;
     ostr << "end index: " << end << " is out of range -1 - "
          << leftOverLength;
-    this->SetError(ostr.str().c_str());
+    this->SetError(ostr.str());
     return false;
     }
 
-  this->Makefile->AddDefinition(variableName.c_str(),
+  this->Makefile->AddDefinition(variableName,
                                 stringValue.substr(begin, end).c_str());
   return true;
 }
@@ -766,7 +766,7 @@ ::HandleLengthCommand(std::vector<std::string> const& args)
   char buffer[1024];
   sprintf(buffer, "%d", static_cast<int>(length));
 
-  this->Makefile->AddDefinition(variableName.c_str(), buffer);
+  this->Makefile->AddDefinition(variableName, buffer);
   return true;
 }
 
@@ -787,7 +787,7 @@ ::HandleConcatCommand(std::vector<std::string> const& args)
     value += args[i];
     }
 
-  this->Makefile->AddDefinition(variableName.c_str(), value.c_str());
+  this->Makefile->AddDefinition(variableName, value.c_str());
   return true;
 }
 
@@ -804,7 +804,7 @@ ::HandleMakeCIdentifierCommand(std::vector<std::string> const& args)
   const std::string& input = args[1];
   const std::string& variableName = args[2];
 
-  this->Makefile->AddDefinition(variableName.c_str(),
+  this->Makefile->AddDefinition(variableName,
                       cmSystemTools::MakeCidentifier(input.c_str()).c_str());
   return true;
 }
@@ -853,7 +853,7 @@ bool cmStringCommand::HandleStripCommand(
     outLength=endPos - startPos + 1;
     }
 
-  this->Makefile->AddDefinition(variableName.c_str(),
+  this->Makefile->AddDefinition(variableName,
     stringValue.substr(startPos, outLength).c_str());
   return true;
 }
@@ -937,7 +937,7 @@ ::HandleRandomCommand(std::vector<std::string> const& args)
     }
   result.push_back(0);
 
-  this->Makefile->AddDefinition(variableName.c_str(), &*result.begin());
+  this->Makefile->AddDefinition(variableName, &*result.begin());
   return true;
 }
 
@@ -977,14 +977,14 @@ ::HandleTimestampCommand(std::vector<std::string> const& args)
       {
       std::string e = " TIMESTAMP sub-command does not recognize option " +
           args[argsIndex] + ".";
-      this->SetError(e.c_str());
+      this->SetError(e);
       return false;
       }
     }
 
   cmTimestamp timestamp;
   std::string result = timestamp.CurrentTime(formatString, utcFlag);
-  this->Makefile->AddDefinition(outputVariable.c_str(), result.c_str());
+  this->Makefile->AddDefinition(outputVariable, result.c_str());
 
   return true;
 }