@@ -265,7 +265,7 @@ bool cmSystemTools::ReadRegistryValue(const char *key, std::string &value)
   HKEY hKey;
   if(RegOpenKeyEx(primaryKey, 
                   second.c_str(), 
-		  0, 
+                  0, 
                   KEY_READ, 
                   &hKey) != ERROR_SUCCESS)
     {
@@ -438,7 +438,7 @@ bool cmSystemTools::DeleteRegistryValue(const char *key)
   HKEY hKey;
   if(RegOpenKeyEx(primaryKey, 
                   second.c_str(), 
-		  0, 
+                  0, 
                   KEY_WRITE, 
                   &hKey) != ERROR_SUCCESS)
     {
@@ -682,7 +682,7 @@ std::string cmSystemTools::ConvertToUnixOutputPath(const char* path)
     char lastch = 1;
     for(const char* ch = ret.c_str(); *ch != '\0'; ++ch)
       {
-	// if it is already escaped then don't try to escape it again
+        // if it is already escaped then don't try to escape it again
       if(*ch == ' ' && lastch != '\\')
         {
         result += '\\';
@@ -790,7 +790,7 @@ bool cmSystemTools::ParseFunction(std::ifstream& fin,
                                   std::string& name,
                                   std::vector<std::string>& arguments,
                                   const char* filename,
-				  bool& parseError)
+                                  bool& parseError)
 {
   parseError = false;
   name = "";
@@ -855,13 +855,13 @@ bool cmSystemTools::ParseFunction(std::ifstream& fin,
             cmSystemTools::GetArguments(line, arguments);
             }
           }
-	else
-	  {
-	  parseError = true;
-	  cmSystemTools::Error("Parse error in read function missing end )\nIn File: ",
-			       filename, "\nCurrent line:", inbuffer);
-	  return false;
-	  }
+        else
+          {
+          parseError = true;
+          cmSystemTools::Error("Parse error in read function missing end )\nIn File: ",
+                               filename, "\nCurrent line:", inbuffer);
+          return false;
+          }
         }
       return true;
       }
@@ -1248,7 +1248,7 @@ bool cmSystemTools::IsOff(const char* val)
     *c = toupper(*c);
     }
   return (v == "OFF" || v == "0" || v == "NO" || v == "FALSE" || 
-	  v == "N" || v == "NOTFOUND" || v == "IGNORE");
+          v == "N" || v == "NOTFOUND" || v == "IGNORE");
 }
 
 
@@ -1326,9 +1326,9 @@ bool WindowsRunCommand(const char* command, const char* dir,
                        std::string& output, int& retVal, bool verbose) 
 {
   //verbose = true;
-  std::cerr << std::endl 
-	    << "WindowsRunCommand(" << command << ")" << std::endl 
-	    << std::flush;
+  //std::cerr << std::endl 
+  //        << "WindowsRunCommand(" << command << ")" << std::endl 
+  //        << std::flush;
   const int BUFFER_SIZE = 4096;
   char buf[BUFFER_SIZE];
  
@@ -1430,11 +1430,11 @@ bool WindowsRunCommand(const char* command, const char* dir,
         {
         while (bread >= 1023) 
           {
-	  //std::cout << "Read data..." << std::endl;
+          //std::cout << "Read data..." << std::endl;
           ReadFile(read_stdout,buf,1023,&bread,NULL);
  
-//read the stdout pipe 
-          printf("%s",buf);
+          //read the stdout pipe 
+          std::cout << buf << std::flush;
           memset(buf, 0, sizeof(buf));
  
           }
@@ -1447,8 +1447,7 @@ bool WindowsRunCommand(const char* command, const char* dir,
         output += "\n";
         if(verbose) 
           {
-          std::cerr << verbose << " [{" << buf << "}]" 
-		    << std::endl << std::flush;
+          std::cout << buf << std::flush;
  
           }
  
@@ -1474,11 +1473,14 @@ bool WindowsRunCommand(const char* command, const char* dir,
 #include "cmWin32ProcessExecution.h"
 // use this for shell commands like echo and dir
 bool RunCommandViaWin32(const char* command,
-			const char* dir,
-			std::string& output,
-			int& retVal,
-			bool verbose)
-{
+                        const char* dir,
+                        std::string& output,
+                        int& retVal,
+                        bool verbose)
+{
+#if defined(__BORLANDC__)
+  return ::WindowsRunCommand(command, dir, output, retVal, verbose);
+#else // Visual studio
   ::SetLastError(ERROR_SUCCESS);
   if ( ! command )
     {
@@ -1505,6 +1507,7 @@ bool RunCommandViaWin32(const char* command,
   output = resProc.GetOutput();
   retVal = resProc.GetExitValue();
   return true;
+#endif
 }
 
 // use this for shell commands like echo and dir
@@ -1630,9 +1633,9 @@ bool cmSystemTools::RunCommand(const char* command,
         //return RunCommandViaSystem(shortCmd.c_str(), dir, 
         //                           output, retVal, verbose);
         //return WindowsRunCommand(shortCmd.c_str(), dir, 
-	//output, retVal, verbose);
+        //output, retVal, verbose);
         return RunCommandViaWin32(shortCmd.c_str(), dir, 
-				  output, retVal, verbose);
+                                  output, retVal, verbose);
         }
       else
         {
@@ -1700,27 +1703,27 @@ bool cmSystemTools::RunCommand(const char* command,
       {
 #ifdef SIGKILL
       case SIGKILL:
-	error << "SIGKILL";
-	break;
+        error << "SIGKILL";
+        break;
 #endif
 #ifdef SIGFPE
       case SIGFPE:
-	error << "SIGFPE";
-	break;
+        error << "SIGFPE";
+        break;
 #endif
 #ifdef SIGBUS
       case SIGBUS:
-	error << "SIGBUS";
-	break;
+        error << "SIGBUS";
+        break;
 #endif
 #ifdef SIGSEGV
       case SIGSEGV:
-	error << "SIGSEGV";
-	break;
+        error << "SIGSEGV";
+        break;
 #endif
       default:
-	error << "signal " << retVal;
-	break;
+        error << "signal " << retVal;
+        break;
       }
     output += error.str();
     }
@@ -1734,7 +1737,7 @@ bool cmSystemTools::RunCommand(const char* command,
  * found.  Otherwise, the empty string is returned.
  */
 std::string cmSystemTools::FindFile(const char* name, 
-				       const std::vector<std::string>& userPaths)
+                                       const std::vector<std::string>& userPaths)
 {
   // Add the system search path to our path.
   std::vector<std::string> path = userPaths;
@@ -1763,7 +1766,7 @@ std::string cmSystemTools::FindFile(const char* name,
  * found.  Otherwise, the empty string is returned.
  */
 std::string cmSystemTools::FindProgram(const char* name,
-				       const std::vector<std::string>& userPaths,
+                                       const std::vector<std::string>& userPaths,
                                        bool no_system_path)
 {
   // See if the executable exists as written.
@@ -1998,8 +2001,8 @@ std::string cmSystemTools::GetProgramPath(const char* in_name)
  * string is returned.
  */
 void cmSystemTools::SplitProgramPath(const char* in_name,
-				     std::string& dir,
-				     std::string& file)
+                                     std::string& dir,
+                                     std::string& file)
 {
   dir = in_name;
   file = "";
@@ -2221,7 +2224,7 @@ void cmSystemTools::Glob(const char *directory, const char *regexp,
   if (d.Load(directory))
     {
     size_t numf;
-	unsigned int i;
+        unsigned int i;
     numf = d.GetNumberOfFiles();
     for (i = 0; i < numf; i++)
       {