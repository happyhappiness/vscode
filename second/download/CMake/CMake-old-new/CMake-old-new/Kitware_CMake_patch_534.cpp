@@ -52,6 +52,21 @@ int main(int argc, char* argv[])
   fprintf(ofp, "#include \"kwsysPrivate.h\"\n");
   fprintf(ofp, "#include KWSYS_HEADER(Configure.h)\n\n");
   fprintf(ofp, "#include <stdio.h>\n\n");
+  fprintf(ofp, "#if defined(_WIN32)\n");
+  fprintf(ofp, "# include <io.h>\n");
+  fprintf(ofp, "#else\n");
+  fprintf(ofp, "# include <unistd.h>\n");
+  fprintf(ofp, "#endif\n");
+  fprintf(ofp, "\n");
+  fprintf(ofp, "static void kwsys_unlink(const char* fname)\n");
+  fprintf(ofp, "{\n");
+  fprintf(ofp, "#if defined(__WATCOMC__)\n");
+  fprintf(ofp, "  unlink(fname);\n");
+  fprintf(ofp, "#else\n");
+  fprintf(ofp, "  _unlink(fname);\n");
+  fprintf(ofp, "#endif\n");
+  fprintf(ofp, "}\n");
+  fprintf(ofp, "\n");
   
   /* Split file up in 1024-byte chunks.  */
   while((n = (int)fread(buffer, 1, 1024, ifp)) > 0)
@@ -78,9 +93,6 @@ int main(int argc, char* argv[])
   fprintf(ofp, "extern %s_EXPORT int %sEncodedWriteArray%s(const char* fname)\n",
           argv[3], argv[3], argv[4]);
   fprintf(ofp, "{\n");
-  fprintf(ofp, "#ifdef __WATCOMC__\n");
-  fprintf(ofp, "#define _unlink unlink\n");
-  fprintf(ofp, "#endif\n");
   fprintf(ofp, "  FILE* ofp = fopen(fname, \"wb\");\n");
   fprintf(ofp, "  if(!ofp) { return 0; }\n");
   for(i=0; i < count; ++i)
@@ -91,7 +103,7 @@ int main(int argc, char* argv[])
             argv[4], i, argv[4], i, argv[4], i);
     fprintf(ofp, "    {\n");
     fprintf(ofp, "    fclose(ofp);\n");
-    fprintf(ofp, "    _unlink(fname);\n");
+    fprintf(ofp, "    kwsys_unlink(fname);\n");
     fprintf(ofp, "    return 0;\n");
     fprintf(ofp, "    }\n");
     }