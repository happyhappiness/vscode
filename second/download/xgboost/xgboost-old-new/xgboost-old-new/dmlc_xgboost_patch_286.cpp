@@ -90,6 +90,7 @@ struct MetaInfo {
   }
   // try to load group information from file, if exists
   inline bool TryLoadGroup(const char* fname, bool silent = false) {
+    using namespace std;
     FILE *fi = fopen64(fname, "r");
     if (fi == NULL) return false;
     group_ptr.push_back(0);
@@ -105,6 +106,7 @@ struct MetaInfo {
     return true;
   }
   inline std::vector<float>& GetFloatInfo(const char *field) {
+    using namespace std;
     if (!strcmp(field, "label")) return labels;
     if (!strcmp(field, "weight")) return weights;
     if (!strcmp(field, "base_margin")) return base_margin;
@@ -115,6 +117,7 @@ struct MetaInfo {
     return ((MetaInfo*)this)->GetFloatInfo(field);
   }
   inline std::vector<unsigned> &GetUIntInfo(const char *field) {
+    using namespace std;
     if (!strcmp(field, "root_index")) return info.root_index;
     if (!strcmp(field, "fold_index")) return info.fold_index;
     utils::Error("unknown field %s", field);
@@ -125,6 +128,7 @@ struct MetaInfo {
   }
   // try to load weight information from file, if exists
   inline bool TryLoadFloatInfo(const char *field, const char* fname, bool silent = false) {
+    using namespace std;
     std::vector<float> &data = this->GetFloatInfo(field);
     FILE *fi = fopen64(fname, "r");
     if (fi == NULL) return false;