@@ -31,7 +31,7 @@ namespace xgboost{
             /*! \brief load feature map from text format */
             inline void LoadText(FILE *fi){
                 int fid;
-                char fname[256], ftype[256];
+                char fname[1256], ftype[1256];
                 while (fscanf(fi, "%d\t%[^\t]\t%s\n", &fid, fname, ftype) == 3){
                     utils::Assert(fid == (int)names_.size(), "invalid fmap format");
                     names_.push_back(std::string(fname));