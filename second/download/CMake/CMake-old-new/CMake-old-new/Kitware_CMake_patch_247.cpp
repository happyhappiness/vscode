@@ -109,7 +109,8 @@ const char* StrNStr(const char* start, const char* find, size_t &size) {
  *----------------------------------------------------------------------
  */
 int
-HaveExportedObjects(PIMAGE_FILE_HEADER pImageFileHeader, PIMAGE_SECTION_HEADER pSectionHeaders)
+HaveExportedObjects(PIMAGE_FILE_HEADER pImageFileHeader,
+                    PIMAGE_SECTION_HEADER pSectionHeaders)
 {
     static int fImportFlag = 0;  /*  The status is nor defined yet */
     WORD i;
@@ -124,12 +125,14 @@ HaveExportedObjects(PIMAGE_FILE_HEADER pImageFileHeader, PIMAGE_SECTION_HEADER p
     i = 0;
     foundExports = 0;
     pDirectivesSectionHeader = 0;
-    for(i = 0; i < pImageFileHeader->NumberOfSections && !pDirectivesSectionHeader; i++)
+    for(i = 0; (i < pImageFileHeader->NumberOfSections &&
+                !pDirectivesSectionHeader); i++)
        if (!strncmp((const char*)&pSectionHeaders[i].Name[0], ".drectve",8))
           pDirectivesSectionHeader = &pSectionHeaders[i];
    if (!pDirectivesSectionHeader) return 0;
 
-    rawdata=(const char*)pImageFileHeader+pDirectivesSectionHeader->PointerToRawData;
+    rawdata=(const char*)
+      pImageFileHeader+pDirectivesSectionHeader->PointerToRawData;
     if (!pDirectivesSectionHeader->PointerToRawData || !rawdata) return 0;
 
     size = pDirectivesSectionHeader->SizeOfRawData;
@@ -164,7 +167,8 @@ HaveExportedObjects(PIMAGE_FILE_HEADER pImageFileHeader, PIMAGE_SECTION_HEADER p
 *----------------------------------------------------------------------
 */
 void
-DumpExternalsObjects(PIMAGE_SYMBOL pSymbolTable, PIMAGE_SECTION_HEADER pSectionHeaders,
+DumpExternalsObjects(PIMAGE_SYMBOL pSymbolTable,
+                     PIMAGE_SECTION_HEADER pSectionHeaders,
                      FILE *fout, unsigned cSymbols)
 {
    unsigned i;
@@ -179,7 +183,8 @@ DumpExternalsObjects(PIMAGE_SYMBOL pSymbolTable, PIMAGE_SECTION_HEADER pSectionH
    stringTable = (PSTR)&pSymbolTable[cSymbols];
 
    for ( i=0; i < cSymbols; i++ ) {
-      if (pSymbolTable->SectionNumber > 0 && ( pSymbolTable->Type == 0x20 || pSymbolTable->Type == 0x0)) {
+      if (pSymbolTable->SectionNumber > 0 &&
+          ( pSymbolTable->Type == 0x20 || pSymbolTable->Type == 0x0)) {
          if (pSymbolTable->StorageClass == IMAGE_SYM_CLASS_EXTERNAL) {
             /*
             *    The name of the Function entry points
@@ -207,12 +212,14 @@ DumpExternalsObjects(PIMAGE_SYMBOL pSymbolTable, PIMAGE_SECTION_HEADER pSectionH
                symbol.compare(0, 4, vectorPrefix) &&
                symbol.find("real@") == std::string::npos)
             {
-               SectChar = pSectionHeaders[pSymbolTable->SectionNumber-1].Characteristics;
+               SectChar =
+                pSectionHeaders[pSymbolTable->SectionNumber-1].Characteristics;
                if (!pSymbolTable->Type  && (SectChar & IMAGE_SCN_MEM_WRITE)) {
                   // Read only (i.e. constants) must be excluded
                   fprintf(fout, "\t%s \t DATA\n", symbol.c_str());
                } else {
-                  if ( pSymbolTable->Type  || !(SectChar & IMAGE_SCN_MEM_READ)) {
+                  if ( pSymbolTable->Type  ||
+                       !(SectChar & IMAGE_SCN_MEM_READ)) {
                      fprintf(fout, "\t%s\n", symbol.c_str());
                   } else {
                      //                    printf(" strange symbol: %s \n",s);
@@ -221,7 +228,8 @@ DumpExternalsObjects(PIMAGE_SYMBOL pSymbolTable, PIMAGE_SECTION_HEADER pSectionH
             }
          }
       }
-      else if (pSymbolTable->SectionNumber == IMAGE_SYM_UNDEFINED && !pSymbolTable->Type && 0){
+      else if (pSymbolTable->SectionNumber == IMAGE_SYM_UNDEFINED &&
+               !pSymbolTable->Type && 0) {
          /*
          *    The IMPORT global variable entry points
          */
@@ -271,9 +279,11 @@ DumpObjFile(PIMAGE_FILE_HEADER pImageFileHeader, FILE *fout)
       pImageFileHeader->SizeOfOptionalHeader);
 
 
-   int haveExports = HaveExportedObjects(pImageFileHeader, PCOFFSectionHeaders);
+   int haveExports = HaveExportedObjects(pImageFileHeader,
+                                         PCOFFSectionHeaders);
    if (!haveExports)
-       DumpExternalsObjects(PCOFFSymbolTable, PCOFFSectionHeaders, fout, COFFSymbolCount);
+       DumpExternalsObjects(PCOFFSymbolTable, PCOFFSectionHeaders,
+                            fout, COFFSymbolCount);
 }
 
 /*
@@ -322,7 +332,8 @@ DumpFile(LPSTR filename, FILE *fout)
    }
    /* Does it look like a i386 COFF OBJ file??? */
    else if (
-           ((dosHeader->e_magic == IMAGE_FILE_MACHINE_I386) || (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64))
+           ((dosHeader->e_magic == IMAGE_FILE_MACHINE_I386) ||
+            (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64))
            && (dosHeader->e_sp == 0)
            ) {
       /*