@@ -33,13 +33,23 @@ struct MetaInfo {
    *  can be used for multi task setting
    */
   std::vector<unsigned> root_index;
+  /*! 
+   * \brief initialized margins,
+   * if specified, xgboost will start from this init margin
+   * can be used to specify initial prediction to boost from
+   */
+  std::vector<float> base_margin;
+  /*! \brief version flag, used to check version of this info */
+  static const int kVersion = 0;
+  // constructor
   MetaInfo(void) : num_row(0), num_col(0) {}
   /*! \brief clear all the information */
   inline void Clear(void) {
     labels.clear();
     group_ptr.clear();
     weights.clear();
     root_index.clear();
+    base_margin.clear();
     num_row = num_col = 0;
   }
   /*! \brief get weight of each instances */
@@ -59,20 +69,26 @@ struct MetaInfo {
     }
   }
   inline void SaveBinary(utils::IStream &fo) const {
+    int version = kVersion;
+    fo.Write(&version, sizeof(version));
     fo.Write(&num_row, sizeof(num_row));
     fo.Write(&num_col, sizeof(num_col));
     fo.Write(labels);
     fo.Write(group_ptr);
     fo.Write(weights);
     fo.Write(root_index);
+    fo.Write(base_margin);
   }
   inline void LoadBinary(utils::IStream &fi) {
+    int version;
+    utils::Check(fi.Read(&version, sizeof(version)), "MetaInfo: invalid format");
     utils::Check(fi.Read(&num_row, sizeof(num_row)), "MetaInfo: invalid format");
     utils::Check(fi.Read(&num_col, sizeof(num_col)), "MetaInfo: invalid format");
     utils::Check(fi.Read(&labels), "MetaInfo: invalid format");
     utils::Check(fi.Read(&group_ptr), "MetaInfo: invalid format");
     utils::Check(fi.Read(&weights), "MetaInfo: invalid format");
     utils::Check(fi.Read(&root_index), "MetaInfo: invalid format");
+    utils::Check(fi.Read(&base_margin), "MetaInfo: invalid format");
   }
   // try to load group information from file, if exists
   inline bool TryLoadGroup(const char* fname, bool silent = false) {
@@ -89,16 +105,27 @@ struct MetaInfo {
     fclose(fi);
     return true;
   }
+  inline std::vector<float>& GetInfo(const char *field) {
+    if (!strcmp(field, "label")) return labels;
+    if (!strcmp(field, "weight")) return weights;
+    if (!strcmp(field, "base_margin")) return base_margin;
+    utils::Error("unknown field %s", field);
+    return labels;
+  }
+  inline const std::vector<float>& GetInfo(const char *field) const {
+    return ((MetaInfo*)this)->GetInfo(field);
+  }
   // try to load weight information from file, if exists
-  inline bool TryLoadWeight(const char* fname, bool silent = false) {
+  inline bool TryLoadFloatInfo(const char *field, const char* fname, bool silent = false) {
+    std::vector<float> &weights = this->GetInfo(field);       
     FILE *fi = fopen64(fname, "r");
     if (fi == NULL) return false;
     float wt;
     while (fscanf(fi, "%f", &wt) == 1) {
       weights.push_back(wt);
     }
     if (!silent) {
-      printf("loading weight from %s\n", fname);
+      printf("loading %s from %s\n", field, fname);
     }
     fclose(fi);
     return true;