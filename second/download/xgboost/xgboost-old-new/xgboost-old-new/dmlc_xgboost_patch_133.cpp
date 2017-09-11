@@ -24,6 +24,10 @@ class SparsePage {
   SparsePage() {
     this->Clear();
   }
+  /*! \return number of instance in the page */
+  inline size_t Size() const {
+    return offset.size() - 1;
+  }
   /*!
    * \brief load the by providing a list of interested segments
    *        only the interested segments are loaded
@@ -38,6 +42,7 @@ class SparsePage {
     offset.clear(); offset.push_back(0);
     for (size_t i = 0; i < sorted_index_set.size(); ++i) {
       bst_uint fid = sorted_index_set[i];
+      utils::Check(fid + 1 < disk_offset_.size(), "bad col.blob format");
       size_t size = disk_offset_[fid + 1] - disk_offset_[fid];
       offset.push_back(offset.back() + size);
     }
@@ -49,7 +54,7 @@ class SparsePage {
       bst_uint fid = sorted_index_set[i];
       if (disk_offset_[fid] != curr_offset) {
         utils::Assert(disk_offset_[fid] > curr_offset, "fset index was not sorted");
-        fi->Seek(begin + disk_offset_[fid]);
+        fi->Seek(begin + disk_offset_[fid] * sizeof(SparseBatch::Entry));
         curr_offset = disk_offset_[fid];
       }
       size_t j, size_to_read = 0;
@@ -68,6 +73,10 @@ class SparsePage {
       }
       i = j;
     }
+    // seek to end of record
+    if (curr_offset != disk_offset_.back()) {
+      fi->Seek(begin + disk_offset_.back() * sizeof(SparseBatch::Entry));
+    }
     return true;
   }
   /*!
@@ -166,7 +175,8 @@ class SparsePage {
  */
 class SparsePageFactory {
  public:
-  SparsePageFactory(void) {}
+  SparsePageFactory(void)
+      : action_load_all_(true), set_load_all_(true) {}
   inline void SetFile(const utils::FileStream &fi,
                       size_t file_begin = 0) {
     fi_ = fi;
@@ -176,19 +186,27 @@ class SparsePageFactory {
     return action_index_set_;
   }
   // set index set, will be used after next before first
-  inline void SetIndexSet(const std::vector<bst_uint> &index_set) {
-    set_index_set_ = index_set;
-    std::sort(set_index_set_.begin(), set_index_set_.end());
+  inline void SetIndexSet(const std::vector<bst_uint> &index_set, 
+                          bool load_all) {
+    set_load_all_ = load_all;
+    if (!set_load_all_) {
+      set_index_set_ = index_set;
+      std::sort(set_index_set_.begin(), set_index_set_.end());
+    }
   }
   inline bool Init(void) {
     return true;
   }
   inline void SetParam(const char *name, const char *val) {}
-  inline bool LoadNext(SparsePage *val) {
-    if (action_index_set_.size() != 0) {
-      return val->Load(&fi_, action_index_set_);
+  inline bool LoadNext(SparsePage *val) {    
+    if (!action_load_all_) {
+      if (action_index_set_.size() == 0) {
+        return false;
+      } else {
+        return val->Load(&fi_, action_index_set_);
+      }
     } else {
-      return val->Load(&fi_);      
+      return val->Load(&fi_);
     }
   }
   inline SparsePage *Create(void) {
@@ -202,10 +220,14 @@ class SparsePageFactory {
   }
   inline void BeforeFirst(void) {
     fi_.Seek(file_begin_);
-    action_index_set_ = set_index_set_;
+    action_load_all_ = set_load_all_;
+    if (!set_load_all_) {
+      action_index_set_ = set_index_set_;
+    }
   }
 
  private:
+  bool action_load_all_, set_load_all_;
   size_t file_begin_;
   utils::FileStream fi_;
   std::vector<bst_uint> action_index_set_;