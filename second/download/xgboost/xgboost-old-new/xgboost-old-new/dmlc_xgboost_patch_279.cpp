@@ -7,8 +7,9 @@
  * \author Tianqi Chen
  */
 #include <vector>
+#include <cstring>
 #include "../data.h"
-
+#include "../utils/io.h"
 namespace xgboost {
 namespace learner {
 /*!
@@ -89,6 +90,7 @@ struct MetaInfo {
   }
   // try to load group information from file, if exists
   inline bool TryLoadGroup(const char* fname, bool silent = false) {
+    using namespace std;
     FILE *fi = fopen64(fname, "r");
     if (fi == NULL) return false;
     group_ptr.push_back(0);
@@ -97,12 +99,14 @@ struct MetaInfo {
       group_ptr.push_back(group_ptr.back()+nline);
     }
     if (!silent) {
-      printf("%lu groups are loaded from %s\n", group_ptr.size()-1, fname);
+      utils::Printf("%u groups are loaded from %s\n",
+                    static_cast<unsigned>(group_ptr.size()-1), fname);
     }
     fclose(fi);
     return true;
   }
   inline std::vector<float>& GetFloatInfo(const char *field) {
+    using namespace std;
     if (!strcmp(field, "label")) return labels;
     if (!strcmp(field, "weight")) return weights;
     if (!strcmp(field, "base_margin")) return base_margin;
@@ -113,6 +117,7 @@ struct MetaInfo {
     return ((MetaInfo*)this)->GetFloatInfo(field);
   }
   inline std::vector<unsigned> &GetUIntInfo(const char *field) {
+    using namespace std;
     if (!strcmp(field, "root_index")) return info.root_index;
     if (!strcmp(field, "fold_index")) return info.fold_index;
     utils::Error("unknown field %s", field);
@@ -123,15 +128,16 @@ struct MetaInfo {
   }
   // try to load weight information from file, if exists
   inline bool TryLoadFloatInfo(const char *field, const char* fname, bool silent = false) {
-    std::vector<float> &weights = this->GetFloatInfo(field);
+    using namespace std;
+    std::vector<float> &data = this->GetFloatInfo(field);
     FILE *fi = fopen64(fname, "r");
     if (fi == NULL) return false;
     float wt;
     while (fscanf(fi, "%f", &wt) == 1) {
-      weights.push_back(wt);
+      data.push_back(wt);
     }
     if (!silent) {
-      printf("loading %s from %s\n", field, fname);
+      utils::Printf("loading %s from %s\n", field, fname);
     }
     fclose(fi);
     return true;
@@ -142,7 +148,6 @@ struct MetaInfo {
  * \brief data object used for learning,
  * \tparam FMatrix type of feature data source
  */
-template<typename FMatrix>
 struct DMatrix {
   /*! 
    * \brief magic number associated with this object 
@@ -151,15 +156,15 @@ struct DMatrix {
   const int magic;
   /*! \brief meta information about the dataset */
   MetaInfo info;
-  /*! \brief feature matrix about data content */
-  FMatrix fmat;
   /*! 
    * \brief cache pointer to verify if the data structure is cached in some learner
    *  used to verify if DMatrix is cached
    */
   void *cache_learner_ptr_;
   /*! \brief default constructor */
   explicit DMatrix(int magic) : magic(magic), cache_learner_ptr_(NULL) {}
+  /*! \brief get feature matrix about data content */
+  virtual IFMatrix *fmat(void) const = 0;
   // virtual destructor
   virtual ~DMatrix(void){}
 };