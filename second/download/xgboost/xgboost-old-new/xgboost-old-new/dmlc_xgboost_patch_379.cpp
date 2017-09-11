@@ -2,6 +2,7 @@
 #define _CRT_SECURE_NO_DEPRECATE
 #include <string>
 #include "./io.h"
+#include "../utils/utils.h"
 #include "simple_dmatrix-inl.hpp"
 // implements data loads using dmatrix simple for now
 
@@ -12,5 +13,10 @@ DataMatrix* LoadDataMatrix(const char *fname, bool silent, bool savebuffer) {
   dmat->CacheLoad(fname, silent, savebuffer);
   return dmat;
 }
+
+void SaveDataMatrix(const DataMatrix &dmat, const char *fname, bool silent) {
+  utils::Error("not implemented");
+}
+
 }  // namespace io
 }  // namespace xgboost