@@ -1,15 +1,32 @@
 #define _CRT_SECURE_NO_WARNINGS
 #define _CRT_SECURE_NO_DEPRECATE
+#define NOMINMAX
 #include <string>
 #include "./io.h"
 #include "../utils/io.h"
 #include "../utils/utils.h"
 #include "simple_dmatrix-inl.hpp"
+#include "page_dmatrix-inl.hpp"
+#include "page_fmatrix-inl.hpp"
+
 // implements data loads using dmatrix simple for now
 
 namespace xgboost {
 namespace io {
 DataMatrix* LoadDataMatrix(const char *fname, bool silent, bool savebuffer) {
+  if (!strcmp(fname, "stdin")) {
+    DMatrixSimple *dmat = new DMatrixSimple();
+    dmat->LoadText(fname, silent);
+    return dmat;
+  }
+  std::string tmp_fname;
+  const char *fname_ext = NULL;
+  if (strchr(fname, ';') != NULL) {
+    tmp_fname = fname;
+    char *ptr = strchr(&tmp_fname[0], ';');
+    ptr[0] = '\0'; fname = &tmp_fname[0];
+    fname_ext = ptr + 1;
+  }
   int magic;
   utils::FileStream fs(utils::FopenCheck(fname, "rb"));
   utils::Check(fs.Read(&magic, sizeof(magic)) != 0, "invalid input file format");
@@ -20,7 +37,27 @@ DataMatrix* LoadDataMatrix(const char *fname, bool silent, bool savebuffer) {
     dmat->LoadBinary(fs, silent, fname);
     fs.Close();
     return dmat;
-  } 
+  }
+  if (magic == DMatrixPage::kMagic) {
+    if (fname_ext == NULL) {
+      DMatrixPage *dmat = new DMatrixPage();
+      dmat->Load(fs, silent, fname);
+      return dmat;
+    } else {
+      DMatrixColPage *dmat = new DMatrixColPage(fname_ext);
+      dmat->Load(fs, silent, fname, true);
+      return dmat;
+    }
+  }
+  if (magic == DMatrixColPage::kMagic) {
+    std::string sfname = fname;
+    if (fname_ext == NULL) {
+      sfname += ".col"; fname_ext = sfname.c_str();
+    }
+    DMatrixColPage *dmat = new DMatrixColPage(fname_ext);
+    dmat->Load(fs, silent, fname);
+    return dmat;
+  }
   fs.Close();
  
   DMatrixSimple *dmat = new DMatrixSimple();
@@ -29,11 +66,21 @@ DataMatrix* LoadDataMatrix(const char *fname, bool silent, bool savebuffer) {
 }
 
 void SaveDataMatrix(const DataMatrix &dmat, const char *fname, bool silent) {
+  if (!strcmp(fname + strlen(fname) - 5, ".page")) {    
+    DMatrixPage::Save(fname, dmat, silent);
+    return;
+  }
+  if (!strcmp(fname + strlen(fname) - 6, ".cpage")) {
+    DMatrixColPage::Save(fname, dmat, silent);
+    return;
+  }
   if (dmat.magic == DMatrixSimple::kMagic) {
     const DMatrixSimple *p_dmat = static_cast<const DMatrixSimple*>(&dmat);
     p_dmat->SaveBinary(fname, silent);
   } else {
-    utils::Error("not implemented");
+    DMatrixSimple smat;
+    smat.CopyFrom(dmat);
+    smat.SaveBinary(fname, silent);
   }
 }
 