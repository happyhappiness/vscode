-
 /*
+ * Copyright (C) 1996-2017 The Squid Software Foundation and contributors
  *
- * SQUID Web Proxy Cache          http://www.squid-cache.org/
- * ----------------------------------------------------------
- *
- *  Squid is the result of efforts by numerous individuals from
- *  the Internet community; see the CONTRIBUTORS file for full
- *  details.   Many organizations have provided support for Squid's
- *  development; see the SPONSORS file for full details.  Squid is
- *  Copyrighted (C) 2001 by the Regents of the University of
- *  California; see the COPYRIGHT file for full details.  Squid
- *  incorporates software developed and/or copyrighted by other
- *  sources; see the CREDITS file for full details.
- *
- *  This program is free software; you can redistribute it and/or modify
- *  it under the terms of the GNU General Public License as published by
- *  the Free Software Foundation; either version 2 of the License, or
- *  (at your option) any later version.
- *
- *  This program is distributed in the hope that it will be useful,
- *  but WITHOUT ANY WARRANTY; without even the implied warranty of
- *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
- *  GNU General Public License for more details.
- *
- *  You should have received a copy of the GNU General Public License
- *  along with this program; if not, write to the Free Software
- *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
- *
- *
- * Copyright (c) 2003, Robert Collins <robertc@squid-cache.org>
+ * Squid software is distributed under GPLv2+ license and includes
+ * contributions from numerous individuals and organizations.
+ * Please see the COPYING and CONTRIBUTORS files for details.
  */
 
 #include "squid.h"
 #include "cache_cf.h"
 #include "ConfigParser.h"
 #include "Debug.h"
 #include "fatal.h"
 #include "globals.h"
 
-char *ConfigParser::lastToken = NULL;
-std::queue<std::string> ConfigParser::undo;
+bool ConfigParser::RecognizeQuotedValues = true;
+bool ConfigParser::StrictMode = true;
+std::stack<ConfigParser::CfgFile *> ConfigParser::CfgFiles;
+ConfigParser::TokenType ConfigParser::LastTokenType = ConfigParser::SimpleToken;
+const char *ConfigParser::CfgLine = NULL;
+const char *ConfigParser::CfgPos = NULL;
+std::queue<char *> ConfigParser::CfgLineTokens_;
+std::queue<std::string> ConfigParser::Undo_;
+bool ConfigParser::AllowMacros_ = false;
+bool ConfigParser::ParseQuotedOrToEol_ = false;
+bool ConfigParser::RecognizeQuotedPair_ = false;
+bool ConfigParser::PreviewMode_ = false;
 
-int ConfigParser::RecognizeQuotedValues = true;
+static const char *SQUID_ERROR_TOKEN = "[invalid token]";
 
 void
 ConfigParser::destruct()
 {
     shutting_down = 1;
-    fatalf("Bungled %s line %d: %s",
-           cfg_filename, config_lineno, config_input_line);
-}
-
-void
-ConfigParser::strtokFileUndo()
-{
-    assert(lastToken);
-    undo.push(lastToken);
+    if (!CfgFiles.empty()) {
+        std::ostringstream message;
+        CfgFile *f = CfgFiles.top();
+        message << "Bungled " << f->filePath << " line " << f->lineNo <<
+                ": " << f->currentLine << std::endl;
+        CfgFiles.pop();
+        delete f;
+        while (!CfgFiles.empty()) {
+            f = CfgFiles.top();
+            message << " included from " << f->filePath << " line " <<
+                    f->lineNo << ": " << f->currentLine << std::endl;
+            CfgFiles.pop();
+            delete f;
+        }
+        message << " included from " <<  cfg_filename << " line " <<
+                config_lineno << ": " << config_input_line << std::endl;
+        std::string msg = message.str();
+        fatalf("%s", msg.c_str());
+    } else
+        fatalf("Bungled %s line %d: %s",
+               cfg_filename, config_lineno, config_input_line);
 }
 
 void
-ConfigParser::strtokFilePutBack(const char *tok)
+ConfigParser::TokenPutBack(const char *tok)
 {
     assert(tok);
-    undo.push(tok);
+    Undo_.push(tok);
 }
 
 char *
-xstrtok(char *str, const char *delimiters)
+ConfigParser::Undo()
 {
-    assert(!str); // we are parsing the configuration file
-    // no support unless enabled in the configuration and
-    // no support for other delimiters (they may need to be eradicated!)
-    return (ConfigParser::RecognizeQuotedValues &&
-            strcmp(delimiters, " \t\n\r") == 0) ?
-           ConfigParser::NextToken() : ::strtok(str, delimiters);
+    LOCAL_ARRAY(char, undoToken, CONFIG_LINE_LIMIT);
+    if (!Undo_.empty()) {
+        strncpy(undoToken, Undo_.front().c_str(), sizeof(undoToken));
+        undoToken[sizeof(undoToken) - 1] = '\0';
+        if (!PreviewMode_)
+            Undo_.pop();
+        return undoToken;
+    }
+    return NULL;
 }
 
 char *
-ConfigParser::strtokFile(void)
+ConfigParser::strtokFile()
 {
+    if (RecognizeQuotedValues)
+        return ConfigParser::NextToken();
+
     static int fromFile = 0;
     static FILE *wordFile = NULL;
-    LOCAL_ARRAY(char, undoToken, CONFIG_LINE_LIMIT);
 
-    char *t, *fn;
+    char *t;
     LOCAL_ARRAY(char, buf, CONFIG_LINE_LIMIT);
 
-    if (!undo.empty()) {
-        strncpy(undoToken, undo.front().c_str(), sizeof(undoToken));
-        undoToken[sizeof(undoToken) - 1] = '\0';
-        undo.pop();
-        return lastToken = undoToken;
-    }
-
-    if (RecognizeQuotedValues)
-        return lastToken = ConfigParser::NextToken();
+    if ((t = ConfigParser::Undo()))
+        return t;
 
-    lastToken = NULL;
     do {
 
         if (!fromFile) {
-            t = (strtok(NULL, w_space));
-
-            if (!t || *t == '#') {
+            ConfigParser::TokenType tokenType;
+            t = ConfigParser::NextElement(tokenType);
+            if (!t) {
                 return NULL;
             } else if (*t == '\"' || *t == '\'') {
                 /* quote found, start reading from file */
-                fn = ++t;
+                debugs(3, 8,"Quoted token found : " << t);
+                char *fn = ++t;
 
                 while (*t && *t != '\"' && *t != '\'')
                     ++t;
 
                 *t = '\0';
 
                 if ((wordFile = fopen(fn, "r")) == NULL) {
-                    debugs(28, DBG_CRITICAL, "strtokFile: " << fn << " not found");
-                    return (NULL);
+                    debugs(3, DBG_CRITICAL, "ERROR: Can not open file " << fn << " for reading");
+                    return NULL;
                 }
 
 #if _SQUID_WINDOWS_
                 setmode(fileno(wordFile), O_TEXT);
 #endif
 
                 fromFile = 1;
             } else {
-                return lastToken = t;
+                return t;
             }
         }
 
         /* fromFile */
         if (fgets(buf, CONFIG_LINE_LIMIT, wordFile) == NULL) {
             /* stop reading from file */
