@@ -70,7 +70,7 @@
 * Author:   Valery Fine 16/09/96  (E-mail: fine@vxcern.cern.ch)
 *----------------------------------------------------------------------
 */
-
+#include "bindexplib.h"
 #include <cmsys/Encoding.hxx>
 #include <windows.h>
 #include <stdio.h>
@@ -173,15 +173,17 @@ class DumpSymbols
    */
 
    DumpSymbols(ObjectHeaderType* ih,
-               FILE* fout, bool is64) {
+               std::set<std::string>& symbols,
+               std::set<std::string>& dataSymbols,
+               bool is64)
+     :Symbols(symbols), DataSymbols(dataSymbols)
+    {
       this->ObjectImageHeader = ih;
       this->SymbolTable = (SymbolTableType*)
       ((DWORD_PTR)this->ObjectImageHeader
        + this->ObjectImageHeader->PointerToSymbolTable);
-      this->FileOut = fout;
       this->SectionHeaders =
         GetSectionHeaderOffset(this->ObjectImageHeader);
-      this->ImportFlag = true;
       this->SymbolCount = this->ObjectImageHeader->NumberOfSymbols;
       this->Is64Bit = is64;
    }
@@ -296,10 +298,6 @@ class DumpSymbols
                 symbol.erase(0,1);
                 }
               }
-            if (this->ImportFlag) {
-               this->ImportFlag = false;
-               fprintf(this->FileOut,"EXPORTS \n");
-            }
             /*
             Check whether it is "Scalar deleting destructor" and
             "Vector deleting destructor"
@@ -319,11 +317,11 @@ class DumpSymbols
                  SectionHeaders[pSymbolTable->SectionNumber-1].Characteristics;
                if (!pSymbolTable->Type  && (SectChar & IMAGE_SCN_MEM_WRITE)) {
                   // Read only (i.e. constants) must be excluded
-                  fprintf(this->FileOut, "\t%s \t DATA\n", symbol.c_str());
+                  this->DataSymbols.insert(symbol);
                } else {
                   if ( pSymbolTable->Type  ||
                        !(SectChar & IMAGE_SCN_MEM_READ)) {
-                     fprintf(this->FileOut, "\t%s\n", symbol.c_str());
+                     this->Symbols.insert(symbol);
                   } else {
                      // printf(" strange symbol: %s \n",symbol.c_str());
                   }
@@ -340,11 +338,7 @@ class DumpSymbols
             symbol = stringTable + pSymbolTable->N.Name.Long;
             while (isspace(symbol[0]))  symbol.erase(0,1);
             if (symbol[0] == '_') symbol.erase(0,1);
-            if (!this->ImportFlag) {
-               this->ImportFlag = true;
-               fprintf(this->FileOut,"IMPORTS \n");
-            }
-            fprintf(this->FileOut, "\t%s DATA \n", symbol.c_str()+1);
+            this->DataSymbols.insert(symbol);
          }
       }
 
@@ -357,8 +351,8 @@ class DumpSymbols
     }
   }
 private:
-  bool ImportFlag;
-  FILE* FileOut;
+  std::set<std::string>& Symbols;
+  std::set<std::string>& DataSymbols;
   DWORD_PTR SymbolCount;
   PIMAGE_SECTION_HEADER SectionHeaders;
   ObjectHeaderType* ObjectImageHeader;
@@ -367,7 +361,9 @@ class DumpSymbols
 };
 
 bool
-DumpFile(const char* filename, FILE *fout)
+DumpFile(const char* filename,
+         std::set<std::string>& symbols,
+         std::set<std::string>& dataSymbols)
 {
    HANDLE hFile;
    HANDLE hFileMapping;
@@ -415,7 +411,7 @@ DumpFile(const char* filename, FILE *fout)
       * and IMAGE_FILE_HEADER.SizeOfOptionalHeader == 0;
       */
       DumpSymbols<IMAGE_FILE_HEADER, IMAGE_SYMBOL>
-        symbolDumper((PIMAGE_FILE_HEADER) lpFileBase, fout,
+        symbolDumper((PIMAGE_FILE_HEADER) lpFileBase, symbols, dataSymbols,
                      (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64));
       symbolDumper.DumpObjFile();
    } else {
@@ -424,7 +420,8 @@ DumpFile(const char* filename, FILE *fout)
         (cmANON_OBJECT_HEADER_BIGOBJ*) lpFileBase;
       if(h->Sig1 == 0x0 && h->Sig2 == 0xffff) {
          DumpSymbols<cmANON_OBJECT_HEADER_BIGOBJ, cmIMAGE_SYMBOL_EX>
-           symbolDumper((cmANON_OBJECT_HEADER_BIGOBJ*) lpFileBase, fout,
+           symbolDumper((cmANON_OBJECT_HEADER_BIGOBJ*) lpFileBase, symbols,
+                        dataSymbols,
                         (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64));
          symbolDumper.DumpObjFile();
       } else {
@@ -437,3 +434,27 @@ DumpFile(const char* filename, FILE *fout)
    CloseHandle(hFile);
    return true;
 }
+
+bool bindexplib::AddObjectFile(const char* filename)
+{
+  if(!DumpFile(filename, this->Symbols, this->DataSymbols))
+    {
+    return false;
+    }
+  return true;
+}
+
+void bindexplib::WriteFile(FILE* file)
+{
+  fprintf(file,"EXPORTS \n");
+  for(std::set<std::string>::const_iterator i = this->DataSymbols.begin();
+      i!= this->DataSymbols.end(); ++i)
+    {
+    fprintf(file, "\t%s \t DATA\n", i->c_str());
+    }
+  for(std::set<std::string>::const_iterator i = this->Symbols.begin();
+      i!= this->Symbols.end(); ++i)
+    {
+    fprintf(file, "\t%s\n", i->c_str());
+    }
+}