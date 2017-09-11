@@ -15,7 +15,12 @@ DataMatrix* LoadDataMatrix(const char *fname, bool silent, bool savebuffer) {
 }
 
 void SaveDataMatrix(const DataMatrix &dmat, const char *fname, bool silent) {
-  utils::Error("not implemented");
+  if (dmat.magic == DMatrixSimple::kMagic){
+    const DMatrixSimple *p_dmat = static_cast<const DMatrixSimple*>(&dmat);
+    p_dmat->SaveBinary(fname, silent);
+  } else {
+    utils::Error("not implemented");
+  }
 }
 
 }  // namespace io