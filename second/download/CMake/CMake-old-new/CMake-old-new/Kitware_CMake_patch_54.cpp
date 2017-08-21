@@ -68,81 +68,84 @@
 #include <iostream>
 #include <windows.h>
 
-typedef struct cmANON_OBJECT_HEADER_BIGOBJ {
-   /* same as ANON_OBJECT_HEADER_V2 */
-    WORD    Sig1;            // Must be IMAGE_FILE_MACHINE_UNKNOWN
-    WORD    Sig2;            // Must be 0xffff
-    WORD    Version;         // >= 2 (implies the Flags field is present)
-    WORD    Machine;         // Actual machine - IMAGE_FILE_MACHINE_xxx
-    DWORD   TimeDateStamp;
-    CLSID   ClassID;         // {D1BAA1C7-BAEE-4ba9-AF20-FAF66AA4DCB8}
-    DWORD   SizeOfData;      // Size of data that follows the header
-    DWORD   Flags;           // 0x1 -> contains metadata
-    DWORD   MetaDataSize;    // Size of CLR metadata
-    DWORD   MetaDataOffset;  // Offset of CLR metadata
-
-    /* bigobj specifics */
-    DWORD   NumberOfSections; // extended from WORD
-    DWORD   PointerToSymbolTable;
-    DWORD   NumberOfSymbols;
+typedef struct cmANON_OBJECT_HEADER_BIGOBJ
+{
+  /* same as ANON_OBJECT_HEADER_V2 */
+  WORD Sig1;    // Must be IMAGE_FILE_MACHINE_UNKNOWN
+  WORD Sig2;    // Must be 0xffff
+  WORD Version; // >= 2 (implies the Flags field is present)
+  WORD Machine; // Actual machine - IMAGE_FILE_MACHINE_xxx
+  DWORD TimeDateStamp;
+  CLSID ClassID;        // {D1BAA1C7-BAEE-4ba9-AF20-FAF66AA4DCB8}
+  DWORD SizeOfData;     // Size of data that follows the header
+  DWORD Flags;          // 0x1 -> contains metadata
+  DWORD MetaDataSize;   // Size of CLR metadata
+  DWORD MetaDataOffset; // Offset of CLR metadata
+
+  /* bigobj specifics */
+  DWORD NumberOfSections; // extended from WORD
+  DWORD PointerToSymbolTable;
+  DWORD NumberOfSymbols;
 } cmANON_OBJECT_HEADER_BIGOBJ;
 
-typedef struct _cmIMAGE_SYMBOL_EX {
-    union {
-        BYTE     ShortName[8];
-        struct {
-            DWORD   Short;     // if 0, use LongName
-            DWORD   Long;      // offset into string table
-        } Name;
-        DWORD   LongName[2];    // PBYTE  [2]
-    } N;
-    DWORD   Value;
-    LONG    SectionNumber;
-    WORD    Type;
-    BYTE    StorageClass;
-    BYTE    NumberOfAuxSymbols;
+typedef struct _cmIMAGE_SYMBOL_EX
+{
+  union
+  {
+    BYTE ShortName[8];
+    struct
+    {
+      DWORD Short; // if 0, use LongName
+      DWORD Long;  // offset into string table
+    } Name;
+    DWORD LongName[2]; // PBYTE  [2]
+  } N;
+  DWORD Value;
+  LONG SectionNumber;
+  WORD Type;
+  BYTE StorageClass;
+  BYTE NumberOfAuxSymbols;
 } cmIMAGE_SYMBOL_EX;
-typedef cmIMAGE_SYMBOL_EX UNALIGNED *cmPIMAGE_SYMBOL_EX;
+typedef cmIMAGE_SYMBOL_EX UNALIGNED* cmPIMAGE_SYMBOL_EX;
 
-PIMAGE_SECTION_HEADER GetSectionHeaderOffset(PIMAGE_FILE_HEADER
-                                             pImageFileHeader)
+PIMAGE_SECTION_HEADER GetSectionHeaderOffset(
+  PIMAGE_FILE_HEADER pImageFileHeader)
 {
-  return (PIMAGE_SECTION_HEADER)
-    ((DWORD_PTR)pImageFileHeader +
-     IMAGE_SIZEOF_FILE_HEADER +
-     pImageFileHeader->SizeOfOptionalHeader);
+  return (PIMAGE_SECTION_HEADER)((DWORD_PTR)pImageFileHeader +
+                                 IMAGE_SIZEOF_FILE_HEADER +
+                                 pImageFileHeader->SizeOfOptionalHeader);
 }
 
-PIMAGE_SECTION_HEADER GetSectionHeaderOffset(cmANON_OBJECT_HEADER_BIGOBJ*
-                                             pImageFileHeader)
+PIMAGE_SECTION_HEADER GetSectionHeaderOffset(
+  cmANON_OBJECT_HEADER_BIGOBJ* pImageFileHeader)
 {
-  return (PIMAGE_SECTION_HEADER)
-      ((DWORD_PTR)pImageFileHeader          +
-       sizeof(cmANON_OBJECT_HEADER_BIGOBJ));
+  return (PIMAGE_SECTION_HEADER)((DWORD_PTR)pImageFileHeader +
+                                 sizeof(cmANON_OBJECT_HEADER_BIGOBJ));
 }
 
 /*
 + * Utility func, strstr with size
 + */
-const char* StrNStr(const char* start, const char* find, size_t &size) {
-   size_t len;
-   const char* hint;
+const char* StrNStr(const char* start, const char* find, size_t& size)
+{
+  size_t len;
+  const char* hint;
 
-   if (!start || !find || !size) {
-      size = 0;
-      return 0;
-   }
-   len = strlen(find);
-
-   while ((hint = (const char*) memchr(start, find[0], size-len+1))) {
-      size -= (hint - start);
-      if (!strncmp(hint, find, len))
-         return hint;
-      start = hint + 1;
-   }
-
-   size = 0;
-   return 0;
+  if (!start || !find || !size) {
+    size = 0;
+    return 0;
+  }
+  len = strlen(find);
+
+  while ((hint = (const char*)memchr(start, find[0], size - len + 1))) {
+    size -= (hint - start);
+    if (!strncmp(hint, find, len))
+      return hint;
+    start = hint + 1;
+  }
+
+  size = 0;
+  return 0;
 }
 
 template <
@@ -162,21 +165,19 @@ class DumpSymbols
    *----------------------------------------------------------------------
    */
 
-   DumpSymbols(ObjectHeaderType* ih,
-               std::set<std::string>& symbols,
-               std::set<std::string>& dataSymbols,
-               bool is64)
-     :Symbols(symbols), DataSymbols(dataSymbols)
-    {
-      this->ObjectImageHeader = ih;
-      this->SymbolTable = (SymbolTableType*)
-      ((DWORD_PTR)this->ObjectImageHeader
-       + this->ObjectImageHeader->PointerToSymbolTable);
-      this->SectionHeaders =
-        GetSectionHeaderOffset(this->ObjectImageHeader);
-      this->SymbolCount = this->ObjectImageHeader->NumberOfSymbols;
-      this->Is64Bit = is64;
-   }
+  DumpSymbols(ObjectHeaderType* ih, std::set<std::string>& symbols,
+              std::set<std::string>& dataSymbols, bool is64)
+    : Symbols(symbols)
+    , DataSymbols(dataSymbols)
+  {
+    this->ObjectImageHeader = ih;
+    this->SymbolTable =
+      (SymbolTableType*)((DWORD_PTR) this->ObjectImageHeader +
+                         this->ObjectImageHeader->PointerToSymbolTable);
+    this->SectionHeaders = GetSectionHeaderOffset(this->ObjectImageHeader);
+    this->SymbolCount = this->ObjectImageHeader->NumberOfSymbols;
+    this->Is64Bit = is64;
+  }
 
   /*
    *----------------------------------------------------------------------
@@ -187,43 +188,49 @@ class DumpSymbols
    *----------------------------------------------------------------------
    */
 
-  bool HaveExportedObjects() {
-     WORD i = 0;
-     size_t size = 0;
-     const char * rawdata = 0;
-     PIMAGE_SECTION_HEADER pDirectivesSectionHeader = 0;
-     PIMAGE_SECTION_HEADER pSectionHeaders = this->SectionHeaders;
-     for(i = 0; (i < this->ObjectImageHeader->NumberOfSections &&
-                 !pDirectivesSectionHeader); i++)
-       if (!strncmp((const char*)&pSectionHeaders[i].Name[0], ".drectve",8))
-         pDirectivesSectionHeader = &pSectionHeaders[i];
-     if (!pDirectivesSectionHeader) return 0;
-
-     rawdata=(const char*)
-       this->ObjectImageHeader+pDirectivesSectionHeader->PointerToRawData;
-     if (!pDirectivesSectionHeader->PointerToRawData || !rawdata) return 0;
-
-     size = pDirectivesSectionHeader->SizeOfRawData;
-     const char* posImportFlag = rawdata;
-     while ((posImportFlag = StrNStr(posImportFlag, " /EXPORT:", size))) {
-       const char* lookingForDict = posImportFlag + 9;
-       if (!strncmp(lookingForDict, "_G__cpp_",8) ||
-           !strncmp(lookingForDict, "_G__set_cpp_",12)) {
-          posImportFlag = lookingForDict;
-          continue;
-       }
-
-       const char* lookingForDATA = posImportFlag + 9;
-       while (*(++lookingForDATA) && *lookingForDATA != ' ');
-       lookingForDATA -= 5;
-       // ignore DATA exports
-       if (strncmp(lookingForDATA, ",DATA", 5)) break;
-       posImportFlag = lookingForDATA + 5;
-     }
-     if(posImportFlag) {
-        return true;
-     }
-     return false;
+  bool HaveExportedObjects()
+  {
+    WORD i = 0;
+    size_t size = 0;
+    const char* rawdata = 0;
+    PIMAGE_SECTION_HEADER pDirectivesSectionHeader = 0;
+    PIMAGE_SECTION_HEADER pSectionHeaders = this->SectionHeaders;
+    for (i = 0; (i < this->ObjectImageHeader->NumberOfSections &&
+                 !pDirectivesSectionHeader);
+         i++)
+      if (!strncmp((const char*)&pSectionHeaders[i].Name[0], ".drectve", 8))
+        pDirectivesSectionHeader = &pSectionHeaders[i];
+    if (!pDirectivesSectionHeader)
+      return 0;
+
+    rawdata = (const char*)this->ObjectImageHeader +
+      pDirectivesSectionHeader->PointerToRawData;
+    if (!pDirectivesSectionHeader->PointerToRawData || !rawdata)
+      return 0;
+
+    size = pDirectivesSectionHeader->SizeOfRawData;
+    const char* posImportFlag = rawdata;
+    while ((posImportFlag = StrNStr(posImportFlag, " /EXPORT:", size))) {
+      const char* lookingForDict = posImportFlag + 9;
+      if (!strncmp(lookingForDict, "_G__cpp_", 8) ||
+          !strncmp(lookingForDict, "_G__set_cpp_", 12)) {
+        posImportFlag = lookingForDict;
+        continue;
+      }
+
+      const char* lookingForDATA = posImportFlag + 9;
+      while (*(++lookingForDATA) && *lookingForDATA != ' ')
+        ;
+      lookingForDATA -= 5;
+      // ignore DATA exports
+      if (strncmp(lookingForDATA, ",DATA", 5))
+        break;
+      posImportFlag = lookingForDATA + 5;
+    }
+    if (posImportFlag) {
+      return true;
+    }
+    return false;
   }
 
   /*
@@ -233,9 +240,7 @@ class DumpSymbols
    *      Dump an object file's exported symbols.
    *----------------------------------------------------------------------
    */
-  void DumpObjFile() {
-    this->DumpExternalsObjects();
-  }
+  void DumpObjFile() { this->DumpExternalsObjects(); }
 
   /*
    *----------------------------------------------------------------------
@@ -244,91 +249,89 @@ class DumpSymbols
    *      Dumps a COFF symbol table from an OBJ.
    *----------------------------------------------------------------------
    */
-  void DumpExternalsObjects() {
+  void DumpExternalsObjects()
+  {
     unsigned i;
     PSTR stringTable;
     std::string symbol;
     DWORD SectChar;
     /*
      * The string table apparently starts right after the symbol table
      */
-    stringTable = (PSTR)&this->SymbolTable[this->SymbolCount];
+    stringTable = (PSTR) & this->SymbolTable[this->SymbolCount];
     SymbolTableType* pSymbolTable = this->SymbolTable;
-    for ( i=0; i < this->SymbolCount; i++ ) {
+    for (i = 0; i < this->SymbolCount; i++) {
       if (pSymbolTable->SectionNumber > 0 &&
-          ( pSymbolTable->Type == 0x20 || pSymbolTable->Type == 0x0)) {
-         if (pSymbolTable->StorageClass == IMAGE_SYM_CLASS_EXTERNAL) {
-            /*
-            *    The name of the Function entry points
-            */
-            if (pSymbolTable->N.Name.Short != 0) {
-               symbol = "";
-               symbol.insert(0, (const char *)pSymbolTable->N.ShortName, 8);
-            } else {
-               symbol = stringTable + pSymbolTable->N.Name.Long;
-            }
+          (pSymbolTable->Type == 0x20 || pSymbolTable->Type == 0x0)) {
+        if (pSymbolTable->StorageClass == IMAGE_SYM_CLASS_EXTERNAL) {
+          /*
+          *    The name of the Function entry points
+          */
+          if (pSymbolTable->N.Name.Short != 0) {
+            symbol = "";
+            symbol.insert(0, (const char*)pSymbolTable->N.ShortName, 8);
+          } else {
+            symbol = stringTable + pSymbolTable->N.Name.Long;
+          }
 
-            // clear out any leading spaces
-            while (isspace(symbol[0])) symbol.erase(0,1);
-            // if it starts with _ and has an @ then it is a __cdecl
-            // so remove the @ stuff for the export
-            if(symbol[0] == '_') {
-               std::string::size_type posAt = symbol.find('@');
-               if (posAt != std::string::npos) {
-                  symbol.erase(posAt);
-               }
+          // clear out any leading spaces
+          while (isspace(symbol[0]))
+            symbol.erase(0, 1);
+          // if it starts with _ and has an @ then it is a __cdecl
+          // so remove the @ stuff for the export
+          if (symbol[0] == '_') {
+            std::string::size_type posAt = symbol.find('@');
+            if (posAt != std::string::npos) {
+              symbol.erase(posAt);
             }
-            // For 64 bit builds we don't need to remove _
-            if(!this->Is64Bit)
-              {
-              if (symbol[0] == '_')
-                {
-                symbol.erase(0,1);
-                }
+          }
+          // For 64 bit builds we don't need to remove _
+          if (!this->Is64Bit) {
+            if (symbol[0] == '_') {
+              symbol.erase(0, 1);
+            }
+          }
+          /*
+          Check whether it is "Scalar deleting destructor" and
+          "Vector deleting destructor"
+          */
+          const char* scalarPrefix = "??_G";
+          const char* vectorPrefix = "??_E";
+          // original code had a check for
+          // symbol.find("real@") == std::string::npos)
+          // but if this disallows memmber functions with the name real
+          // if scalarPrefix and vectorPrefix are not found then print
+          // the symbol
+          if (symbol.compare(0, 4, scalarPrefix) &&
+              symbol.compare(0, 4, vectorPrefix)) {
+            SectChar = this->SectionHeaders[pSymbolTable->SectionNumber - 1]
+                         .Characteristics;
+            if (!pSymbolTable->Type && (SectChar & IMAGE_SCN_MEM_WRITE)) {
+              // Read only (i.e. constants) must be excluded
+              this->DataSymbols.insert(symbol);
+            } else {
+              if (pSymbolTable->Type || !(SectChar & IMAGE_SCN_MEM_READ) ||
+                  (SectChar & IMAGE_SCN_MEM_EXECUTE)) {
+                this->Symbols.insert(symbol);
+              } else {
+                // printf(" strange symbol: %s \n",symbol.c_str());
               }
-            /*
-            Check whether it is "Scalar deleting destructor" and
-            "Vector deleting destructor"
-            */
-            const char *scalarPrefix = "??_G";
-            const char *vectorPrefix = "??_E";
-            // original code had a check for
-            // symbol.find("real@") == std::string::npos)
-            // but if this disallows memmber functions with the name real
-            // if scalarPrefix and vectorPrefix are not found then print
-            // the symbol
-            if (symbol.compare(0, 4, scalarPrefix) &&
-                symbol.compare(0, 4, vectorPrefix) )
-            {
-               SectChar =
-                 this->
-                 SectionHeaders[pSymbolTable->SectionNumber-1].Characteristics;
-               if (!pSymbolTable->Type  && (SectChar & IMAGE_SCN_MEM_WRITE)) {
-                  // Read only (i.e. constants) must be excluded
-                  this->DataSymbols.insert(symbol);
-               } else {
-                  if ( pSymbolTable->Type  ||
-                       !(SectChar & IMAGE_SCN_MEM_READ) ||
-                       (SectChar & IMAGE_SCN_MEM_EXECUTE)) {
-                     this->Symbols.insert(symbol);
-                  } else {
-                     // printf(" strange symbol: %s \n",symbol.c_str());
-                  }
-               }
             }
-         }
-      }
-      else if (pSymbolTable->SectionNumber == IMAGE_SYM_UNDEFINED &&
-               !pSymbolTable->Type && 0) {
-         /*
-         *    The IMPORT global variable entry points
-         */
-         if (pSymbolTable->StorageClass == IMAGE_SYM_CLASS_EXTERNAL) {
-            symbol = stringTable + pSymbolTable->N.Name.Long;
-            while (isspace(symbol[0]))  symbol.erase(0,1);
-            if (symbol[0] == '_') symbol.erase(0,1);
-            this->DataSymbols.insert(symbol);
-         }
+          }
+        }
+      } else if (pSymbolTable->SectionNumber == IMAGE_SYM_UNDEFINED &&
+                 !pSymbolTable->Type && 0) {
+        /*
+        *    The IMPORT global variable entry points
+        */
+        if (pSymbolTable->StorageClass == IMAGE_SYM_CLASS_EXTERNAL) {
+          symbol = stringTable + pSymbolTable->N.Name.Long;
+          while (isspace(symbol[0]))
+            symbol.erase(0, 1);
+          if (symbol[0] == '_')
+            symbol.erase(0, 1);
+          this->DataSymbols.insert(symbol);
+        }
       }
 
       /*
@@ -339,89 +342,84 @@ class DumpSymbols
       pSymbolTable++;
     }
   }
+
 private:
   std::set<std::string>& Symbols;
   std::set<std::string>& DataSymbols;
   DWORD_PTR SymbolCount;
   PIMAGE_SECTION_HEADER SectionHeaders;
   ObjectHeaderType* ObjectImageHeader;
-  SymbolTableType*  SymbolTable;
+  SymbolTableType* SymbolTable;
   bool Is64Bit;
 };
 
-bool
-DumpFile(const char* filename,
-         std::set<std::string>& symbols,
-         std::set<std::string>& dataSymbols)
+bool DumpFile(const char* filename, std::set<std::string>& symbols,
+              std::set<std::string>& dataSymbols)
 {
-   HANDLE hFile;
-   HANDLE hFileMapping;
-   LPVOID lpFileBase;
-   PIMAGE_DOS_HEADER dosHeader;
+  HANDLE hFile;
+  HANDLE hFileMapping;
+  LPVOID lpFileBase;
+  PIMAGE_DOS_HEADER dosHeader;
 
-   hFile = CreateFileW(cmsys::Encoding::ToWide(filename).c_str(),
-                       GENERIC_READ, FILE_SHARE_READ, NULL,
-      OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
+  hFile = CreateFileW(cmsys::Encoding::ToWide(filename).c_str(), GENERIC_READ,
+                      FILE_SHARE_READ, NULL, OPEN_EXISTING,
+                      FILE_ATTRIBUTE_NORMAL, 0);
 
-   if (hFile == INVALID_HANDLE_VALUE) {
-      fprintf(stderr, "Couldn't open file '%s' with CreateFile()\n", filename);
-      return false;
-   }
+  if (hFile == INVALID_HANDLE_VALUE) {
+    fprintf(stderr, "Couldn't open file '%s' with CreateFile()\n", filename);
+    return false;
+  }
 
-   hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
-   if (hFileMapping == 0) {
-      CloseHandle(hFile);
-      fprintf(stderr, "Couldn't open file mapping with CreateFileMapping()\n");
-      return false;
-   }
+  hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
+  if (hFileMapping == 0) {
+    CloseHandle(hFile);
+    fprintf(stderr, "Couldn't open file mapping with CreateFileMapping()\n");
+    return false;
+  }
 
-   lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
-   if (lpFileBase == 0) {
-      CloseHandle(hFileMapping);
-      CloseHandle(hFile);
-      fprintf(stderr, "Couldn't map view of file with MapViewOfFile()\n");
-      return false;
-   }
+  lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
+  if (lpFileBase == 0) {
+    CloseHandle(hFileMapping);
+    CloseHandle(hFile);
+    fprintf(stderr, "Couldn't map view of file with MapViewOfFile()\n");
+    return false;
+  }
 
-   dosHeader = (PIMAGE_DOS_HEADER)lpFileBase;
-   if (dosHeader->e_magic == IMAGE_DOS_SIGNATURE) {
-      fprintf(stderr, "File is an executable.  I don't dump those.\n");
-      return false;
-   }
-   /* Does it look like a i386 COFF OBJ file??? */
-   else if (
-           ((dosHeader->e_magic == IMAGE_FILE_MACHINE_I386) ||
-            (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64))
-           && (dosHeader->e_sp == 0)
-           ) {
-      /*
-      * The two tests above aren't what they look like.  They're
-      * really checking for IMAGE_FILE_HEADER.Machine == i386 (0x14C)
-      * and IMAGE_FILE_HEADER.SizeOfOptionalHeader == 0;
-      */
-      DumpSymbols<IMAGE_FILE_HEADER, IMAGE_SYMBOL>
-        symbolDumper((PIMAGE_FILE_HEADER) lpFileBase, symbols, dataSymbols,
-                     (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64));
+  dosHeader = (PIMAGE_DOS_HEADER)lpFileBase;
+  if (dosHeader->e_magic == IMAGE_DOS_SIGNATURE) {
+    fprintf(stderr, "File is an executable.  I don't dump those.\n");
+    return false;
+  }
+  /* Does it look like a i386 COFF OBJ file??? */
+  else if (((dosHeader->e_magic == IMAGE_FILE_MACHINE_I386) ||
+            (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64)) &&
+           (dosHeader->e_sp == 0)) {
+    /*
+    * The two tests above aren't what they look like.  They're
+    * really checking for IMAGE_FILE_HEADER.Machine == i386 (0x14C)
+    * and IMAGE_FILE_HEADER.SizeOfOptionalHeader == 0;
+    */
+    DumpSymbols<IMAGE_FILE_HEADER, IMAGE_SYMBOL> symbolDumper(
+      (PIMAGE_FILE_HEADER)lpFileBase, symbols, dataSymbols,
+      (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64));
+    symbolDumper.DumpObjFile();
+  } else {
+    // check for /bigobj format
+    cmANON_OBJECT_HEADER_BIGOBJ* h = (cmANON_OBJECT_HEADER_BIGOBJ*)lpFileBase;
+    if (h->Sig1 == 0x0 && h->Sig2 == 0xffff) {
+      DumpSymbols<cmANON_OBJECT_HEADER_BIGOBJ, cmIMAGE_SYMBOL_EX> symbolDumper(
+        (cmANON_OBJECT_HEADER_BIGOBJ*)lpFileBase, symbols, dataSymbols,
+        (h->Machine == IMAGE_FILE_MACHINE_AMD64));
       symbolDumper.DumpObjFile();
-   } else {
-      // check for /bigobj format
-      cmANON_OBJECT_HEADER_BIGOBJ* h =
-        (cmANON_OBJECT_HEADER_BIGOBJ*) lpFileBase;
-      if(h->Sig1 == 0x0 && h->Sig2 == 0xffff) {
-         DumpSymbols<cmANON_OBJECT_HEADER_BIGOBJ, cmIMAGE_SYMBOL_EX>
-           symbolDumper((cmANON_OBJECT_HEADER_BIGOBJ*) lpFileBase, symbols,
-                        dataSymbols,
-                        (h->Machine == IMAGE_FILE_MACHINE_AMD64));
-         symbolDumper.DumpObjFile();
-      } else {
-         printf("unrecognized file format in '%s'\n", filename);
-         return false;
-      }
-   }
-   UnmapViewOfFile(lpFileBase);
-   CloseHandle(hFileMapping);
-   CloseHandle(hFile);
-   return true;
+    } else {
+      printf("unrecognized file format in '%s'\n", filename);
+      return false;
+    }
+  }
+  UnmapViewOfFile(lpFileBase);
+  CloseHandle(hFileMapping);
+  CloseHandle(hFile);
+  return true;
 }
 
 bool bindexplib::AddObjectFile(const char* filename)
@@ -431,35 +429,35 @@ bool bindexplib::AddObjectFile(const char* filename)
 
 bool bindexplib::AddDefinitionFile(const char* filename)
 {
-   cmsys::ifstream infile(filename);
-   if (!infile) {
-     fprintf(stderr, "Couldn't open definition file '%s'\n", filename);
-     return false;
-   }
-   std::string str;
-   while (std::getline(infile, str)) {
-     // skip the LIBRAY and EXPORTS lines (if any)
-     if ((str.compare(0,7,"LIBRARY") == 0) ||
-         (str.compare(0,7,"EXPORTS") == 0)) {
-       continue;
-     }
-     // remove leading tabs & spaces
-     str.erase(0, str.find_first_not_of(" \t"));
-     std::size_t found = str.find(" \t DATA");
-     if (found != std::string::npos) {
-       str.erase (found, std::string::npos);
-       this->DataSymbols.insert(str);
-     } else {
-       this->Symbols.insert(str);
-     }
-   }
-   infile.close();
-   return true;
+  cmsys::ifstream infile(filename);
+  if (!infile) {
+    fprintf(stderr, "Couldn't open definition file '%s'\n", filename);
+    return false;
+  }
+  std::string str;
+  while (std::getline(infile, str)) {
+    // skip the LIBRAY and EXPORTS lines (if any)
+    if ((str.compare(0, 7, "LIBRARY") == 0) ||
+        (str.compare(0, 7, "EXPORTS") == 0)) {
+      continue;
+    }
+    // remove leading tabs & spaces
+    str.erase(0, str.find_first_not_of(" \t"));
+    std::size_t found = str.find(" \t DATA");
+    if (found != std::string::npos) {
+      str.erase(found, std::string::npos);
+      this->DataSymbols.insert(str);
+    } else {
+      this->Symbols.insert(str);
+    }
+  }
+  infile.close();
+  return true;
 }
 
 void bindexplib::WriteFile(FILE* file)
 {
-  fprintf(file,"EXPORTS \n");
+  fprintf(file, "EXPORTS \n");
   for (std::set<std::string>::const_iterator i = this->DataSymbols.begin();
        i != this->DataSymbols.end(); ++i) {
     fprintf(file, "\t%s \t DATA\n", i->c_str());