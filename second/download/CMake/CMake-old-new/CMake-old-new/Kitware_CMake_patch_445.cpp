@@ -578,8 +578,8 @@ static void outputDepFile(const string& dfile, const string& objfile,
     tmp = *i;
     doEscape(tmp, "\\", "/");
     doEscape(tmp, " ", "\\ ");
-    //doEscape(tmp, "(", "("); // TODO ninja cant read ( and )
-    //doEscape(tmp, ")", ")");
+    //doEscape(tmp, "(", "\\("); // TODO ninja can't read ( and )
+    //doEscape(tmp, ")", "\\)");
     fprintf(out, "%s \\\n", tmp.c_str());
   }
 
@@ -637,12 +637,9 @@ int main() {
   string line;
   vector<string> includes;
   bool isFirstLine = true; // cl prints always first the source filename
-  std::string sysHeadersCamel =    "Program Files (x86)\\Microsoft ";
-  std::string sysHeadersLower = "program files (x86)\\microsoft ";
   while (getline(ss, line)) {
     if (startsWith(line, prefix)) {
-       if (!contains(line, sysHeadersCamel)
-           && !contains(line, sysHeadersLower)) {
+       if (!contains(line, "(") && !contains(line, ")")) {
         string inc = trimLeadingSpace(line.substr(prefix.size()).c_str());
         if (inc[inc.size() - 1] == '\r') // blech, stupid \r\n
           inc = inc.substr(0, inc.size() - 1);