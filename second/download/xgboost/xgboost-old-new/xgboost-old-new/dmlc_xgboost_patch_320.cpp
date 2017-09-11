@@ -15,10 +15,12 @@ namespace learner {
  * \brief meta information needed in training, including label, weight
  */
 struct MetaInfo {
-  /*! \brief number of rows in the data */
-  size_t num_row;
-  /*! \brief number of columns in the data */
-  size_t num_col;
+  /*! 
+   * \brief information needed by booster 
+   * BoosterInfo does not implement save and load,
+   * all serialization is done in MetaInfo
+   */
+  BoosterInfo info;
   /*! \brief label of each instance */
   std::vector<float> labels;
   /*!
@@ -28,8 +30,6 @@ struct MetaInfo {
   std::vector<bst_uint> group_ptr;
   /*! \brief weights of each instance, optional */
   std::vector<float> weights;
-  /*! \brief information needed by booster */
-  BoosterInfo info;
   /*! 
    * \brief initialized margins,
    * if specified, xgboost will start from this init margin
@@ -39,15 +39,23 @@ struct MetaInfo {
   /*! \brief version flag, used to check version of this info */
   static const int kVersion = 0;
   // constructor
-  MetaInfo(void) : num_row(0), num_col(0) {}
+  MetaInfo(void) {}
+  /*! \return number of rows in dataset */
+  inline size_t num_row(void) const {
+    return info.num_row;
+  }
+  /*! \return number of columns in dataset */
+  inline size_t num_col(void) const {
+    return info.num_col;
+  }
   /*! \brief clear all the information */
   inline void Clear(void) {
     labels.clear();
     group_ptr.clear();
     weights.clear();
     info.root_index.clear();
     base_margin.clear();
-    num_row = num_col = 0;
+    info.num_row = info.num_col = 0;
   }
   /*! \brief get weight of each instances */
   inline float GetWeight(size_t i) const {
@@ -60,8 +68,8 @@ struct MetaInfo {
   inline void SaveBinary(utils::IStream &fo) const {
     int version = kVersion;
     fo.Write(&version, sizeof(version));
-    fo.Write(&num_row, sizeof(num_row));
-    fo.Write(&num_col, sizeof(num_col));
+    fo.Write(&info.num_row, sizeof(info.num_row));
+    fo.Write(&info.num_col, sizeof(info.num_col));
     fo.Write(labels);
     fo.Write(group_ptr);
     fo.Write(weights);
@@ -70,9 +78,9 @@ struct MetaInfo {
   }
   inline void LoadBinary(utils::IStream &fi) {
     int version;
-    utils::Check(fi.Read(&version, sizeof(version)), "MetaInfo: invalid format");
-    utils::Check(fi.Read(&num_row, sizeof(num_row)), "MetaInfo: invalid format");
-    utils::Check(fi.Read(&num_col, sizeof(num_col)), "MetaInfo: invalid format");
+    utils::Check(fi.Read(&version, sizeof(version)) != 0, "MetaInfo: invalid format");
+    utils::Check(fi.Read(&info.num_row, sizeof(info.num_row)) != 0, "MetaInfo: invalid format");
+    utils::Check(fi.Read(&info.num_col, sizeof(info.num_col)) != 0, "MetaInfo: invalid format");
     utils::Check(fi.Read(&labels), "MetaInfo: invalid format");
     utils::Check(fi.Read(&group_ptr), "MetaInfo: invalid format");
     utils::Check(fi.Read(&weights), "MetaInfo: invalid format");
@@ -94,19 +102,28 @@ struct MetaInfo {
     fclose(fi);
     return true;
   }
-  inline std::vector<float>& GetInfo(const char *field) {
+  inline std::vector<float>& GetFloatInfo(const char *field) {
     if (!strcmp(field, "label")) return labels;
     if (!strcmp(field, "weight")) return weights;
     if (!strcmp(field, "base_margin")) return base_margin;
     utils::Error("unknown field %s", field);
     return labels;
   }
-  inline const std::vector<float>& GetInfo(const char *field) const {
-    return ((MetaInfo*)this)->GetInfo(field);
+  inline const std::vector<float>& GetFloatInfo(const char *field) const {
+    return ((MetaInfo*)this)->GetFloatInfo(field);
+  }
+  inline std::vector<unsigned> &GetUIntInfo(const char *field) {
+    if (!strcmp(field, "root_index")) return info.root_index;
+    if (!strcmp(field, "fold_index")) return info.fold_index;
+    utils::Error("unknown field %s", field);
+    return info.root_index;
+  }
+  inline const std::vector<unsigned> &GetUIntInfo(const char *field) const {
+    return ((MetaInfo*)this)->GetUIntInfo(field);
   }
   // try to load weight information from file, if exists
   inline bool TryLoadFloatInfo(const char *field, const char* fname, bool silent = false) {
-    std::vector<float> &weights = this->GetInfo(field);
+    std::vector<float> &weights = this->GetFloatInfo(field);
     FILE *fi = fopen64(fname, "r");
     if (fi == NULL) return false;
     float wt;