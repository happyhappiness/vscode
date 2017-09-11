@@ -5,6 +5,9 @@
 #include "../utils/io.h"
 #include "../utils/utils.h"
 #include "simple_dmatrix-inl.hpp"
+#include "page_dmatrix-inl.hpp"
+#include "page_fmatrix-inl.hpp"
+
 // implements data loads using dmatrix simple for now
 
 namespace xgboost {
@@ -20,7 +23,19 @@ DataMatrix* LoadDataMatrix(const char *fname, bool silent, bool savebuffer) {
     dmat->LoadBinary(fs, silent, fname);
     fs.Close();
     return dmat;
-  } 
+  }
+  if (magic == DMatrixPage::kMagic) {
+    DMatrixPage *dmat = new DMatrixPage();
+    dmat->Load(fs, silent, fname);
+    // the file pointer is hold in page matrix
+    return dmat;
+  }
+  if (magic == DMatrixColPage::kMagic) {
+    DMatrixColPage *dmat = new DMatrixColPage(fname);
+    dmat->Load(fs, silent, fname);
+    // the file pointer is hold in page matrix
+    return dmat;
+  }
   fs.Close();
  
   DMatrixSimple *dmat = new DMatrixSimple();
@@ -29,11 +44,21 @@ DataMatrix* LoadDataMatrix(const char *fname, bool silent, bool savebuffer) {
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
 