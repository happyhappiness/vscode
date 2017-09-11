@@ -1,6 +1,5 @@
 #include "./linear.h"
-#include "../utils/io.h"
-#include "../utils/base64.h"
+#include "../io/io.h"
 
 namespace rabit {
 namespace linear {
@@ -55,7 +54,9 @@ class LinearObjFunction : public solver::IObjFunction<float> {
     }
     if (task == "train") {
       lbfgs.Run();
-      this->SaveModel(model_out.c_str(), lbfgs.GetWeight());
+      if (rabit::GetRank() == 0) {
+        this->SaveModel(model_out.c_str(), lbfgs.GetWeight());
+      }
     } else if (task == "pred") {
       this->TaskPred();
     } else {
@@ -74,51 +75,37 @@ class LinearObjFunction : public solver::IObjFunction<float> {
     printf("Finishing writing to %s\n", name_pred.c_str());
   }
   inline void LoadModel(const char *fname) {
-    FILE *fp = utils::FopenCheck(fname, "rb");
+    IStream *fi = io::CreateStream(fname, "r");
     std::string header; header.resize(4);
     // check header for different binary encode
     // can be base64 or binary
-    utils::FileStream fi(fp);
-    utils::Check(fi.Read(&header[0], 4) != 0, "invalid model");
-      // base64 format
+    utils::Check(fi->Read(&header[0], 4) != 0, "invalid model");
+    // base64 format
     if (header == "bs64") {
-      utils::Base64InStream bsin(fp);
+      io::Base64InStream bsin(fi);
       bsin.InitPosition();
       model.Load(bsin);
-      fclose(fp);
-      return;
     } else if (header == "binf") {
-      model.Load(fi);
-      fclose(fp);
-      return;     
+      model.Load(*fi);
     } else {
       utils::Error("invalid model file");
     }
+    delete fi;
   }
   inline void SaveModel(const char *fname,
                         const float *wptr,
                         bool save_base64 = false) {
-    FILE *fp;
-    bool use_stdout = false;
-    if (!strcmp(fname, "stdout")) {
-      fp = stdout;
-      use_stdout = true;
-    } else {
-      fp = utils::FopenCheck(fname, "wb");
-   }
-    utils::FileStream fo(fp);
-    if (save_base64 != 0|| use_stdout) {
-      fo.Write("bs64\t", 5);
-      utils::Base64OutStream bout(fp);
+    IStream *fo = io::CreateStream(fname, "w");
+    if (save_base64 != 0 || !strcmp(fname, "stdout")) {
+      fo->Write("bs64\t", 5);
+      io::Base64OutStream bout(fo);
       model.Save(bout, wptr);
       bout.Finish('\n');
     } else {
-      fo.Write("binf", 4);
-      model.Save(fo, wptr);
-    }
-    if (!use_stdout) {
-      fclose(fp);
+      fo->Write("binf", 4);
+      model.Save(*fo, wptr);
     }
+    delete fo;
   }
   inline void LoadData(const char *fname) {
     dtrain.Load(fname);