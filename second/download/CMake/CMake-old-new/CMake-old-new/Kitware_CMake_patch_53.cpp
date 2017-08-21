@@ -68,6 +68,10 @@
 #include <iostream>
 #include <windows.h>
 
+#ifndef IMAGE_FILE_MACHINE_ARMNT
+#define IMAGE_FILE_MACHINE_ARMNT 0x01c4
+#endif
+
 typedef struct cmANON_OBJECT_HEADER_BIGOBJ
 {
   /* same as ANON_OBJECT_HEADER_V2 */
@@ -166,7 +170,7 @@ class DumpSymbols
    */
 
   DumpSymbols(ObjectHeaderType* ih, std::set<std::string>& symbols,
-              std::set<std::string>& dataSymbols, bool is64)
+              std::set<std::string>& dataSymbols, bool isI386)
     : Symbols(symbols)
     , DataSymbols(dataSymbols)
   {
@@ -176,7 +180,7 @@ class DumpSymbols
                          this->ObjectImageHeader->PointerToSymbolTable);
     this->SectionHeaders = GetSectionHeaderOffset(this->ObjectImageHeader);
     this->SymbolCount = this->ObjectImageHeader->NumberOfSymbols;
-    this->Is64Bit = is64;
+    this->IsI386 = isI386;
   }
 
   /*
@@ -231,12 +235,11 @@ class DumpSymbols
               symbol.erase(posAt);
             }
           }
-          // For 64 bit builds we don't need to remove _
-          if (!this->Is64Bit) {
-            if (symbol[0] == '_') {
-              symbol.erase(0, 1);
-            }
+          // For i386 builds we don't need to remove _
+          if (this->IsI386 && symbol[0] == '_') {
+            symbol.erase(0, 1);
           }
+
           /*
           Check whether it is "Scalar deleting destructor" and
           "Vector deleting destructor"
@@ -283,7 +286,7 @@ class DumpSymbols
   PIMAGE_SECTION_HEADER SectionHeaders;
   ObjectHeaderType* ObjectImageHeader;
   SymbolTableType* SymbolTable;
-  bool Is64Bit;
+  bool IsI386;
 };
 
 bool DumpFile(const char* filename, std::set<std::string>& symbols,
@@ -323,9 +326,10 @@ bool DumpFile(const char* filename, std::set<std::string>& symbols,
     fprintf(stderr, "File is an executable.  I don't dump those.\n");
     return false;
   }
-  /* Does it look like a i386 COFF OBJ file??? */
+  /* Does it look like a COFF OBJ file??? */
   else if (((dosHeader->e_magic == IMAGE_FILE_MACHINE_I386) ||
-            (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64)) &&
+            (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64) ||
+            (dosHeader->e_magic == IMAGE_FILE_MACHINE_ARMNT)) &&
            (dosHeader->e_sp == 0)) {
     /*
     * The two tests above aren't what they look like.  They're
@@ -334,15 +338,15 @@ bool DumpFile(const char* filename, std::set<std::string>& symbols,
     */
     DumpSymbols<IMAGE_FILE_HEADER, IMAGE_SYMBOL> symbolDumper(
       (PIMAGE_FILE_HEADER)lpFileBase, symbols, dataSymbols,
-      (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64));
+      (dosHeader->e_magic == IMAGE_FILE_MACHINE_I386));
     symbolDumper.DumpObjFile();
   } else {
     // check for /bigobj format
     cmANON_OBJECT_HEADER_BIGOBJ* h = (cmANON_OBJECT_HEADER_BIGOBJ*)lpFileBase;
     if (h->Sig1 == 0x0 && h->Sig2 == 0xffff) {
       DumpSymbols<cmANON_OBJECT_HEADER_BIGOBJ, cmIMAGE_SYMBOL_EX> symbolDumper(
         (cmANON_OBJECT_HEADER_BIGOBJ*)lpFileBase, symbols, dataSymbols,
-        (h->Machine == IMAGE_FILE_MACHINE_AMD64));
+        (h->Machine == IMAGE_FILE_MACHINE_I386));
       symbolDumper.DumpObjFile();
     } else {
       printf("unrecognized file format in '%s'\n", filename);