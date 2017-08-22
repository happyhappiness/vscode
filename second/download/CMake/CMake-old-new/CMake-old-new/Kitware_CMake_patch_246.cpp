@@ -296,7 +296,8 @@ DumpObjFile(PIMAGE_FILE_HEADER pImageFileHeader, FILE *fout)
 *      dumping routine
 *----------------------------------------------------------------------
 */
-void
+
+bool
 DumpFile(const char* filename, FILE *fout)
 {
    HANDLE hFile;
@@ -309,29 +310,29 @@ DumpFile(const char* filename, FILE *fout)
       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
 
    if (hFile == INVALID_HANDLE_VALUE) {
-      fprintf(stderr, "Couldn't open file with CreateFile()\n");
-      return;
+      fprintf(stderr, "Couldn't open file '%s' with CreateFile()\n", filename);
+      return false;
    }
 
    hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hFileMapping == 0) {
       CloseHandle(hFile);
       fprintf(stderr, "Couldn't open file mapping with CreateFileMapping()\n");
-      return;
+      return false;
    }
 
    lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
    if (lpFileBase == 0) {
       CloseHandle(hFileMapping);
       CloseHandle(hFile);
       fprintf(stderr, "Couldn't map view of file with MapViewOfFile()\n");
-      return;
+      return false;
    }
 
    dosHeader = (PIMAGE_DOS_HEADER)lpFileBase;
    if (dosHeader->e_magic == IMAGE_DOS_SIGNATURE) {
       fprintf(stderr, "File is an executable.  I don't dump those.\n");
-      return;
+      return false;
    }
    /* Does it look like a i386 COFF OBJ file??? */
    else if (
@@ -346,9 +347,11 @@ DumpFile(const char* filename, FILE *fout)
       */
       DumpObjFile((PIMAGE_FILE_HEADER) lpFileBase, fout);
    } else {
-      printf("unrecognized file format\n");
+      printf("unrecognized file format in '%s'\n", filename);
+      return false;
    }
    UnmapViewOfFile(lpFileBase);
    CloseHandle(hFileMapping);
    CloseHandle(hFile);
+   return true;
 }