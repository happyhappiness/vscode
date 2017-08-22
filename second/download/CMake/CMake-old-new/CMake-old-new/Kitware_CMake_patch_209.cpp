@@ -173,7 +173,7 @@ class DumpSymbols
    */
 
    DumpSymbols(ObjectHeaderType* ih,
-               FILE* fout) {
+               FILE* fout, bool is64) {
       this->ObjectImageHeader = ih;
       this->SymbolTable = (SymbolTableType*)
       ((DWORD_PTR)this->ObjectImageHeader
@@ -183,6 +183,7 @@ class DumpSymbols
         GetSectionHeaderOffset(this->ObjectImageHeader);
       this->ImportFlag = true;
       this->SymbolCount = this->ObjectImageHeader->NumberOfSymbols;
+      this->Is64Bit = is64;
    }
 
   /*
@@ -287,7 +288,14 @@ class DumpSymbols
                   symbol.erase(posAt);
                }
             }
-            if (symbol[0] == '_') symbol.erase(0,1);
+            // For 64 bit builds we don't need to remove _
+            if(!this->Is64Bit)
+              {
+              if (symbol[0] == '_')
+                {
+                symbol.erase(0,1);
+                }
+              }
             if (this->ImportFlag) {
                this->ImportFlag = false;
                fprintf(this->FileOut,"EXPORTS \n");
@@ -355,6 +363,7 @@ class DumpSymbols
   PIMAGE_SECTION_HEADER SectionHeaders;
   ObjectHeaderType* ObjectImageHeader;
   SymbolTableType*  SymbolTable;
+  bool Is64Bit;
 };
 
 bool
@@ -406,15 +415,17 @@ DumpFile(const char* filename, FILE *fout)
       * and IMAGE_FILE_HEADER.SizeOfOptionalHeader == 0;
       */
       DumpSymbols<IMAGE_FILE_HEADER, IMAGE_SYMBOL>
-        symbolDumper((PIMAGE_FILE_HEADER) lpFileBase, fout);
+        symbolDumper((PIMAGE_FILE_HEADER) lpFileBase, fout,
+                     (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64));
       symbolDumper.DumpObjFile();
    } else {
       // check for /bigobj format
       cmANON_OBJECT_HEADER_BIGOBJ* h =
         (cmANON_OBJECT_HEADER_BIGOBJ*) lpFileBase;
       if(h->Sig1 == 0x0 && h->Sig2 == 0xffff) {
          DumpSymbols<cmANON_OBJECT_HEADER_BIGOBJ, cmIMAGE_SYMBOL_EX>
-           symbolDumper((cmANON_OBJECT_HEADER_BIGOBJ*) lpFileBase, fout);
+           symbolDumper((cmANON_OBJECT_HEADER_BIGOBJ*) lpFileBase, fout,
+                        (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64));
          symbolDumper.DumpObjFile();
       } else {
          printf("unrecognized file format in '%s'\n", filename);