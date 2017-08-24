@@ -78,6 +78,59 @@
 #include <fstream>
 #include <iostream>
 
+typedef struct cmANON_OBJECT_HEADER_BIGOBJ {
+   /* same as ANON_OBJECT_HEADER_V2 */
+    WORD    Sig1;            // Must be IMAGE_FILE_MACHINE_UNKNOWN
+    WORD    Sig2;            // Must be 0xffff
+    WORD    Version;         // >= 2 (implies the Flags field is present)
+    WORD    Machine;         // Actual machine - IMAGE_FILE_MACHINE_xxx
+    DWORD   TimeDateStamp;
+    CLSID   ClassID;         // {D1BAA1C7-BAEE-4ba9-AF20-FAF66AA4DCB8}
+    DWORD   SizeOfData;      // Size of data that follows the header
+    DWORD   Flags;           // 0x1 -> contains metadata
+    DWORD   MetaDataSize;    // Size of CLR metadata
+    DWORD   MetaDataOffset;  // Offset of CLR metadata
+
+    /* bigobj specifics */
+    DWORD   NumberOfSections; // extended from WORD
+    DWORD   PointerToSymbolTable;
+    DWORD   NumberOfSymbols;
+} cmANON_OBJECT_HEADER_BIGOBJ;
+
+typedef struct _cmIMAGE_SYMBOL_EX {
+    union {
+        BYTE     ShortName[8];
+        struct {
+            DWORD   Short;     // if 0, use LongName
+            DWORD   Long;      // offset into string table
+        } Name;
+        DWORD   LongName[2];    // PBYTE  [2]
+    } N;
+    DWORD   Value;
+    LONG    SectionNumber;
+    WORD    Type;
+    BYTE    StorageClass;
+    BYTE    NumberOfAuxSymbols;
+} cmIMAGE_SYMBOL_EX;
+typedef cmIMAGE_SYMBOL_EX UNALIGNED *cmPIMAGE_SYMBOL_EX;
+
+PIMAGE_SECTION_HEADER GetSectionHeaderOffset(PIMAGE_FILE_HEADER
+                                             pImageFileHeader)
+{
+  return (PIMAGE_SECTION_HEADER)
+    ((DWORD_PTR)pImageFileHeader +
+     IMAGE_SIZEOF_FILE_HEADER +
+     pImageFileHeader->SizeOfOptionalHeader);
+}
+
+PIMAGE_SECTION_HEADER GetSectionHeaderOffset(cmANON_OBJECT_HEADER_BIGOBJ*
+                                             pImageFileHeader)
+{
+  return (PIMAGE_SECTION_HEADER)
+      ((DWORD_PTR)pImageFileHeader          +
+       sizeof(cmANON_OBJECT_HEADER_BIGOBJ));
+}
+
 /*
 + * Utility func, strstr with size
 + */
@@ -102,44 +155,64 @@ const char* StrNStr(const char* start, const char* find, size_t &size) {
    return 0;
 }
 
-/*
- *----------------------------------------------------------------------
- * HaveExportedObjects --
- *
- *      Returns >0 if export directives (declspec(dllexport)) exist.
- *
- *----------------------------------------------------------------------
- */
-int
-HaveExportedObjects(PIMAGE_FILE_HEADER pImageFileHeader,
-                    PIMAGE_SECTION_HEADER pSectionHeaders)
+template <
+  // cmANON_OBJECT_HEADER_BIGOBJ or IMAGE_FILE_HEADER
+  class ObjectHeaderType,
+  // cmPIMAGE_SYMBOL_EX or PIMAGE_SYMBOL
+  class SymbolTableType>
+class DumpSymbols
 {
-    static int fImportFlag = 0;  /*  The status is nor defined yet */
-    WORD i;
-    size_t size;
-    char foundExports;
-    const char * rawdata;
+public:
+  /*
+   *----------------------------------------------------------------------
+   * Constructor --
+   *
+   *     Initialize variables from pointer to object header.
+   *
+   *----------------------------------------------------------------------
+   */
 
-    PIMAGE_SECTION_HEADER pDirectivesSectionHeader;
+   DumpSymbols(ObjectHeaderType* ih,
+               FILE* fout) {
+      this->ObjectImageHeader = ih;
+      this->SymbolTable = (SymbolTableType*)
+      ((DWORD_PTR)this->ObjectImageHeader
+       + this->ObjectImageHeader->PointerToSymbolTable);
+      this->FileOut = fout;
+      this->SectionHeaders =
+        GetSectionHeaderOffset(this->ObjectImageHeader);
+      this->ImportFlag = true;
+      this->SymbolCount = this->ObjectImageHeader->NumberOfSymbols;
+   }
 
-    if (fImportFlag) return 1;
+  /*
+   *----------------------------------------------------------------------
+   * HaveExportedObjects --
+   *
+   *      Returns true if export directives (declspec(dllexport)) exist.
+   *
+   *----------------------------------------------------------------------
+   */
 
-    i = 0;
-    foundExports = 0;
-    pDirectivesSectionHeader = 0;
-    for(i = 0; (i < pImageFileHeader->NumberOfSections &&
-                !pDirectivesSectionHeader); i++)
+  bool HaveExportedObjects() {
+     WORD i = 0;
+     size_t size = 0;
+     const char * rawdata = 0;
+     PIMAGE_SECTION_HEADER pDirectivesSectionHeader = 0;
+     PIMAGE_SECTION_HEADER pSectionHeaders = this->SectionHeaders;
+     for(i = 0; (i < this->ObjectImageHeader->NumberOfSections &&
+                 !pDirectivesSectionHeader); i++)
        if (!strncmp((const char*)&pSectionHeaders[i].Name[0], ".drectve",8))
-          pDirectivesSectionHeader = &pSectionHeaders[i];
-   if (!pDirectivesSectionHeader) return 0;
+         pDirectivesSectionHeader = &pSectionHeaders[i];
+     if (!pDirectivesSectionHeader) return 0;
 
-    rawdata=(const char*)
-      pImageFileHeader+pDirectivesSectionHeader->PointerToRawData;
-    if (!pDirectivesSectionHeader->PointerToRawData || !rawdata) return 0;
+     rawdata=(const char*)
+       this->ObjectImageHeader+pDirectivesSectionHeader->PointerToRawData;
+     if (!pDirectivesSectionHeader->PointerToRawData || !rawdata) return 0;
 
-    size = pDirectivesSectionHeader->SizeOfRawData;
-    const char* posImportFlag = rawdata;
-    while ((posImportFlag = StrNStr(posImportFlag, " /EXPORT:", size))) {
+     size = pDirectivesSectionHeader->SizeOfRawData;
+     const char* posImportFlag = rawdata;
+     while ((posImportFlag = StrNStr(posImportFlag, " /EXPORT:", size))) {
        const char* lookingForDict = posImportFlag + 9;
        if (!strncmp(lookingForDict, "_G__cpp_",8) ||
            !strncmp(lookingForDict, "_G__set_cpp_",12)) {
@@ -153,38 +226,44 @@ HaveExportedObjects(PIMAGE_FILE_HEADER pImageFileHeader,
        // ignore DATA exports
        if (strncmp(lookingForDATA, ",DATA", 5)) break;
        posImportFlag = lookingForDATA + 5;
-    }
-    fImportFlag = (int)posImportFlag;
-    return fImportFlag;
-}
-
-
-
-/*
- *----------------------------------------------------------------------
-* DumpExternalsObjects --
-*
-*      Dumps a COFF symbol table from an EXE or OBJ.  We only use
-*      it to dump tables from OBJs.
-*----------------------------------------------------------------------
-*/
-void
-DumpExternalsObjects(PIMAGE_SYMBOL pSymbolTable,
-                     PIMAGE_SECTION_HEADER pSectionHeaders,
-                     FILE *fout, DWORD_PTR cSymbols)
-{
-   unsigned i;
-   PSTR stringTable;
-   std::string symbol;
-   DWORD SectChar;
-   static int fImportFlag = -1;  /*  The status is nor defined yet */
-
-   /*
-   * The string table apparently starts right after the symbol table
+     }
+     if(posImportFlag) {
+        return true;
+     }
+     return false;
+  }
+
+  /*
+   *----------------------------------------------------------------------
+   * DumpObjFile --
+   *
+   *      Dump an object file's exported symbols.
+   *----------------------------------------------------------------------
    */
-   stringTable = (PSTR)&pSymbolTable[cSymbols];
-
-   for ( i=0; i < cSymbols; i++ ) {
+  void DumpObjFile() {
+     if(!HaveExportedObjects()) {
+        this->DumpExternalsObjects();
+     }
+  }
+
+  /*
+   *----------------------------------------------------------------------
+   * DumpExternalsObjects --
+   *
+   *      Dumps a COFF symbol table from an OBJ.
+   *----------------------------------------------------------------------
+   */
+  void DumpExternalsObjects() {
+    unsigned i;
+    PSTR stringTable;
+    std::string symbol;
+    DWORD SectChar;
+    /*
+     * The string table apparently starts right after the symbol table
+     */
+    stringTable = (PSTR)&this->SymbolTable[this->SymbolCount];
+    SymbolTableType* pSymbolTable = this->SymbolTable;
+    for ( i=0; i < this->SymbolCount; i++ ) {
       if (pSymbolTable->SectionNumber > 0 &&
           ( pSymbolTable->Type == 0x20 || pSymbolTable->Type == 0x0)) {
          if (pSymbolTable->StorageClass == IMAGE_SYM_CLASS_EXTERNAL) {
@@ -209,9 +288,9 @@ DumpExternalsObjects(PIMAGE_SYMBOL pSymbolTable,
                }
             }
             if (symbol[0] == '_') symbol.erase(0,1);
-            if (fImportFlag) {
-               fImportFlag = 0;
-               fprintf(fout,"EXPORTS \n");
+            if (this->ImportFlag) {
+               this->ImportFlag = false;
+               fprintf(this->FileOut,"EXPORTS \n");
             }
             /*
             Check whether it is "Scalar deleting destructor" and
@@ -228,14 +307,15 @@ DumpExternalsObjects(PIMAGE_SYMBOL pSymbolTable,
                 symbol.compare(0, 4, vectorPrefix) )
             {
                SectChar =
-                pSectionHeaders[pSymbolTable->SectionNumber-1].Characteristics;
+                 this->
+                 SectionHeaders[pSymbolTable->SectionNumber-1].Characteristics;
                if (!pSymbolTable->Type  && (SectChar & IMAGE_SCN_MEM_WRITE)) {
                   // Read only (i.e. constants) must be excluded
-                  fprintf(fout, "\t%s \t DATA\n", symbol.c_str());
+                  fprintf(this->FileOut, "\t%s \t DATA\n", symbol.c_str());
                } else {
                   if ( pSymbolTable->Type  ||
                        !(SectChar & IMAGE_SCN_MEM_READ)) {
-                     fprintf(fout, "\t%s\n", symbol.c_str());
+                     fprintf(this->FileOut, "\t%s\n", symbol.c_str());
                   } else {
                      // printf(" strange symbol: %s \n",symbol.c_str());
                   }
@@ -252,11 +332,11 @@ DumpExternalsObjects(PIMAGE_SYMBOL pSymbolTable,
             symbol = stringTable + pSymbolTable->N.Name.Long;
             while (isspace(symbol[0]))  symbol.erase(0,1);
             if (symbol[0] == '_') symbol.erase(0,1);
-            if (!fImportFlag) {
-               fImportFlag = 1;
-               fprintf(fout,"IMPORTS \n");
+            if (!this->ImportFlag) {
+               this->ImportFlag = true;
+               fprintf(this->FileOut,"IMPORTS \n");
             }
-            fprintf(fout, "\t%s DATA \n", symbol.c_str()+1);
+            fprintf(this->FileOut, "\t%s DATA \n", symbol.c_str()+1);
          }
       }
 
@@ -266,49 +346,16 @@ DumpExternalsObjects(PIMAGE_SYMBOL pSymbolTable,
       i += pSymbolTable->NumberOfAuxSymbols;
       pSymbolTable += pSymbolTable->NumberOfAuxSymbols;
       pSymbolTable++;
-   }
-}
-
-/*
-*----------------------------------------------------------------------
-* DumpObjFile --
-*
-*      Dump an object file--either a full listing or just the exported
-*      symbols.
-*----------------------------------------------------------------------
-*/
-void
-DumpObjFile(PIMAGE_FILE_HEADER pImageFileHeader, FILE *fout)
-{
-   PIMAGE_SYMBOL PCOFFSymbolTable;
-   PIMAGE_SECTION_HEADER PCOFFSectionHeaders;
-   DWORD_PTR COFFSymbolCount;
-
-   PCOFFSymbolTable = (PIMAGE_SYMBOL)
-      ((DWORD_PTR)pImageFileHeader + pImageFileHeader->PointerToSymbolTable);
-   COFFSymbolCount = pImageFileHeader->NumberOfSymbols;
-
-   PCOFFSectionHeaders = (PIMAGE_SECTION_HEADER)
-      ((DWORD_PTR)pImageFileHeader          +
-      IMAGE_SIZEOF_FILE_HEADER +
-      pImageFileHeader->SizeOfOptionalHeader);
-
-
-   int haveExports = HaveExportedObjects(pImageFileHeader,
-                                         PCOFFSectionHeaders);
-   if (!haveExports)
-       DumpExternalsObjects(PCOFFSymbolTable, PCOFFSectionHeaders,
-                            fout, COFFSymbolCount);
-}
-
-/*
-*----------------------------------------------------------------------
-* DumpFile --
-*
-*      Open up a file, memory map it, and call the appropriate
-*      dumping routine
-*----------------------------------------------------------------------
-*/
+    }
+  }
+private:
+  bool ImportFlag;
+  FILE* FileOut;
+  DWORD_PTR SymbolCount;
+  PIMAGE_SECTION_HEADER SectionHeaders;
+  ObjectHeaderType* ObjectImageHeader;
+  SymbolTableType*  SymbolTable;
+};
 
 bool
 DumpFile(const char* filename, FILE *fout)
@@ -358,10 +405,21 @@ DumpFile(const char* filename, FILE *fout)
       * really checking for IMAGE_FILE_HEADER.Machine == i386 (0x14C)
       * and IMAGE_FILE_HEADER.SizeOfOptionalHeader == 0;
       */
-      DumpObjFile((PIMAGE_FILE_HEADER) lpFileBase, fout);
+      DumpSymbols<IMAGE_FILE_HEADER, IMAGE_SYMBOL>
+        symbolDumper((PIMAGE_FILE_HEADER) lpFileBase, fout);
+      symbolDumper.DumpObjFile();
    } else {
-      printf("unrecognized file format in '%s'\n", filename);
-      return false;
+      // check for /bigobj format
+      cmANON_OBJECT_HEADER_BIGOBJ* h =
+        (cmANON_OBJECT_HEADER_BIGOBJ*) lpFileBase;
+      if(h->Sig1 == 0x0 && h->Sig2 == 0xffff) {
+         DumpSymbols<cmANON_OBJECT_HEADER_BIGOBJ, cmIMAGE_SYMBOL_EX>
+           symbolDumper((cmANON_OBJECT_HEADER_BIGOBJ*) lpFileBase, fout);
+         symbolDumper.DumpObjFile();
+      } else {
+         printf("unrecognized file format in '%s'\n", filename);
+         return false;
+      }
    }
    UnmapViewOfFile(lpFileBase);
    CloseHandle(hFileMapping);