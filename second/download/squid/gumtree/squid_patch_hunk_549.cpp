 #include "cache_cf.h"
 #include "ConfigParser.h"
 #include "Debug.h"
 #include "fatal.h"
 #include "globals.h"
 
+char *ConfigParser::lastToken = NULL;
+std::queue<std::string> ConfigParser::undo;
+
+int ConfigParser::RecognizeQuotedValues = true;
+
 void
 ConfigParser::destruct()
 {
     shutting_down = 1;
     fatalf("Bungled %s line %d: %s",
            cfg_filename, config_lineno, config_input_line);
 }
 
+void
+ConfigParser::strtokFileUndo()
+{
+    assert(lastToken);
+    undo.push(lastToken);
+}
+
+void
+ConfigParser::strtokFilePutBack(const char *tok)
+{
+    assert(tok);
+    undo.push(tok);
+}
+
+char *
+xstrtok(char *str, const char *delimiters)
+{
+    assert(!str); // we are parsing the configuration file
+    // no support unless enabled in the configuration and
+    // no support for other delimiters (they may need to be eradicated!)
+    return (ConfigParser::RecognizeQuotedValues &&
+            strcmp(delimiters, " \t\n\r") == 0) ?
+           ConfigParser::NextToken() : ::strtok(str, delimiters);
+}
+
 char *
 ConfigParser::strtokFile(void)
 {
     static int fromFile = 0;
     static FILE *wordFile = NULL;
+    LOCAL_ARRAY(char, undoToken, CONFIG_LINE_LIMIT);
 
     char *t, *fn;
     LOCAL_ARRAY(char, buf, CONFIG_LINE_LIMIT);
 
+    if (!undo.empty()) {
+        strncpy(undoToken, undo.front().c_str(), sizeof(undoToken));
+        undoToken[sizeof(undoToken) - 1] = '\0';
+        undo.pop();
+        return lastToken = undoToken;
+    }
+
+    if (RecognizeQuotedValues)
+        return lastToken = ConfigParser::NextToken();
+
+    lastToken = NULL;
     do {
 
         if (!fromFile) {
             t = (strtok(NULL, w_space));
 
             if (!t || *t == '#') {
