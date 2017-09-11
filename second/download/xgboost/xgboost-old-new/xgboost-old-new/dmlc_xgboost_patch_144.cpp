@@ -75,7 +75,7 @@ class LinearObjFunction : public solver::IObjFunction<float> {
     printf("Finishing writing to %s\n", name_pred.c_str());
   }
   inline void LoadModel(const char *fname) {
-    IStream *fi = io::CreateStream(fname, "r");
+    Stream *fi = io::CreateStream(fname, "r");
     std::string header; header.resize(4);
     // check header for different binary encode
     // can be base64 or binary
@@ -84,9 +84,9 @@ class LinearObjFunction : public solver::IObjFunction<float> {
     if (header == "bs64") {
       io::Base64InStream bsin(fi);
       bsin.InitPosition();
-      model.Load(bsin);
+      model.Load(&bsin);
     } else if (header == "binf") {
-      model.Load(*fi);
+      model.Load(fi);
     } else {
       utils::Error("invalid model file");
     }
@@ -95,15 +95,15 @@ class LinearObjFunction : public solver::IObjFunction<float> {
   inline void SaveModel(const char *fname,
                         const float *wptr,
                         bool save_base64 = false) {
-    IStream *fo = io::CreateStream(fname, "w");
+    Stream *fo = io::CreateStream(fname, "w");
     if (save_base64 != 0 || !strcmp(fname, "stdout")) {
       fo->Write("bs64\t", 5);
       io::Base64OutStream bout(fo);
-      model.Save(bout, wptr);
+      model.Save(&bout, wptr);
       bout.Finish('\n');
     } else {
       fo->Write("binf", 4);
-      model.Save(*fo, wptr);
+      model.Save(fo, wptr);
     }
     delete fo;
   }
@@ -128,11 +128,11 @@ class LinearObjFunction : public solver::IObjFunction<float> {
     }
   }
   // load model
-  virtual void Load(rabit::IStream &fi) {
-    fi.Read(&model.param, sizeof(model.param));
+  virtual void Load(rabit::Stream *fi) {
+    fi->Read(&model.param, sizeof(model.param));
   }
-  virtual void Save(rabit::IStream &fo) const {
-    fo.Write(&model.param, sizeof(model.param));
+  virtual void Save(rabit::Stream *fo) const {
+    fo->Write(&model.param, sizeof(model.param));
   }
   virtual double Eval(const float *weight, size_t size) {
    if (nthread != 0) omp_set_num_threads(nthread);