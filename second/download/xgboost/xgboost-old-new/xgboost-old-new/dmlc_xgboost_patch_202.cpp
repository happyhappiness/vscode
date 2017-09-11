@@ -32,7 +32,7 @@ class BoostLearnTask {
       }
     }
     // do not save anything when save to stdout
-    if (model_out == "stdout") {
+    if (model_out == "stdout" || name_pred == "stdout") {
       this->SetParam("silent", "1");
       save_period = 0;
     }
@@ -235,12 +235,17 @@ class BoostLearnTask {
     std::vector<float> preds;
     if (!silent) printf("start prediction...\n");
     learner.Predict(*data, pred_margin != 0, &preds, ntree_limit);
-    if (!silent) printf("writing prediction to %s\n", name_pred.c_str());
-    FILE *fo = utils::FopenCheck(name_pred.c_str(), "w");
-    for (size_t i = 0; i < preds.size(); i++) {
-      fprintf(fo, "%f\n", preds[i]);
+    if (!silent) printf("writing prediction to %s\n", name_pred.c_str());    
+    FILE *fo;
+    if (name_pred != "stdout") {
+      fo = utils::FopenCheck(name_pred.c_str(), "w");
+    } else {
+      fo = stdout;
     }
-    fclose(fo);
+    for (size_t i = 0; i < preds.size(); ++i) {
+      fprintf(fo, "%g\n", preds[i]);
+    }
+    if (fo != stdout) fclose(fo);
   }
  private:
   /*! \brief whether silent */