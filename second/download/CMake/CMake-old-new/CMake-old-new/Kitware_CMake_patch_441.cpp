@@ -580,8 +580,6 @@ static void outputDepFile(const string& dfile, const string& objfile,
     tmp = *i;
     doEscape(tmp, "\\", "/");
     doEscape(tmp, " ", "\\ ");
-    //doEscape(tmp, "(", "\\("); // TODO ninja can't read ( and )
-    //doEscape(tmp, ")", "\\)");
     fprintf(out, "%s \\\n", tmp.c_str());
     //printf("include: %s \n", tmp.c_str());
   }
@@ -640,12 +638,10 @@ static int process( const string& srcfilename,
   bool isFirstLine = true; // cl prints always first the source filename
   while (getline(ss, line)) {
     if (startsWith(line, prefix)) {
-       if (!contains(line, "(") && !contains(line, ")")) {
-        string inc = trimLeadingSpace(line.substr(prefix.size()).c_str());
-        if (inc[inc.size() - 1] == '\r') // blech, stupid \r\n
-          inc = inc.substr(0, inc.size() - 1);
-        includes.push_back(inc);
-       }
+      string inc = trimLeadingSpace(line.substr(prefix.size()).c_str());
+      if (inc[inc.size() - 1] == '\r') // blech, stupid \r\n
+        inc = inc.substr(0, inc.size() - 1);
+      includes.push_back(inc);
     } else {
       if (!isFirstLine || !startsWith(line, srcfilename)) {
         if (!quiet) {