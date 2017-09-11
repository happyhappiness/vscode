@@ -13,6 +13,7 @@
 #include "../utils/omp.h"
 #include "../utils/utils.h"
 #include "../sync/sync.h"
+#include "../utils/thread_buffer.h"
 #include "./sparse_batch_page.h"
 
 namespace xgboost {
@@ -29,13 +30,19 @@ struct LibSVMPage : public SparsePage {
 /*!
  * \brief libsvm parser that parses the input lines
  * and returns rows in input data
+ * factry that was used by threadbuffer template
  */
-class LibSVMParser : public utils::IIterator<LibSVMPage> {
+class LibSVMPageFactory  {
  public:
-  explicit LibSVMParser(dmlc::InputSplit *source,
-                        int nthread)
-      : bytes_read_(0), at_head_(true),
-        data_ptr_(0), data_end_(0), source_(source) {
+  explicit LibSVMPageFactory() 
+      : bytes_read_(0), at_head_(true) {
+  }
+  inline bool Init(void) {
+    return true;
+  }
+  inline void Setup(dmlc::InputSplit *source,
+                    int nthread) {
+    source_ = source;
     int maxthread;
     #pragma omp parallel
     {
@@ -44,34 +51,28 @@ class LibSVMParser : public utils::IIterator<LibSVMPage> {
     maxthread = std::max(maxthread / 2, 1);
     nthread_ = std::min(maxthread, nthread);
   }
-  virtual ~LibSVMParser() {
-    delete source_;
+  inline void SetParam(const char *name, const char *val) {}
+  inline bool LoadNext(std::vector<LibSVMPage> *data) {
+    return FillData(data);
   }
-  virtual void BeforeFirst(void) {
-    utils::Assert(at_head_, "cannot call BeforeFirst");
+  inline void FreeSpace(std::vector<LibSVMPage> *a) {
+    delete a;
   }
-  virtual const LibSVMPage &Value(void) const {
-    return data_[data_ptr_ - 1];
+  inline std::vector<LibSVMPage> *Create(void) {
+    return new std::vector<LibSVMPage>();
   }
-  virtual bool Next(void) {
-    while (true) {
-      while (data_ptr_ < data_end_) {
-        data_ptr_ += 1;
-        if (data_[data_ptr_ - 1].Size() != 0) {
-          return true;
-        }
-      }
-      if (!FillData()) break;
-      data_ptr_ = 0; data_end_ = data_.size();
-    }
-    return false;
+  inline void BeforeFirst(void) {
+    utils::Assert(at_head_, "cannot call beforefirst");
+  }
+  inline void Destroy(void) {
+    delete source_;
   }
   inline size_t bytes_read(void) const {
     return bytes_read_;
   }
 
  protected:
-  inline bool FillData() {
+  inline bool FillData(std::vector<LibSVMPage> *data) {
     dmlc::InputSplit::Blob chunk;
     if (!source_->NextChunk(&chunk)) return false;
     int nthread;
@@ -80,7 +81,7 @@ class LibSVMParser : public utils::IIterator<LibSVMPage> {
       nthread = omp_get_num_threads();
     }
     // reserve space for data
-    data_.resize(nthread);
+    data->resize(nthread);
     bytes_read_ += chunk.size;
     utils::Assert(chunk.size != 0, "LibSVMParser.FileData");
     char *head = reinterpret_cast<char*>(chunk.dptr);        
@@ -98,9 +99,8 @@ class LibSVMParser : public utils::IIterator<LibSVMPage> {
       } else {
         pend = BackFindEndLine(head + send, head);
       }
-      ParseBlock(pbegin, pend, &data_[tid]);
+      ParseBlock(pbegin, pend, &(*data)[tid]);
     }
-    data_ptr_ = 0;
     return true;
   }
   /*!
@@ -156,13 +156,54 @@ class LibSVMParser : public utils::IIterator<LibSVMPage> {
   size_t bytes_read_;
   // at beginning, at end of stream
   bool at_head_;
-  // pointer to begin and end of data
-  size_t data_ptr_, data_end_;
   // source split that provides the data
   dmlc::InputSplit *source_;
-  // internal data
-  std::vector<LibSVMPage> data_;
 };
+
+class LibSVMParser : public utils::IIterator<LibSVMPage> {
+ public:
+  explicit LibSVMParser(dmlc::InputSplit *source,
+                        int nthread)
+      : at_end_(false), data_ptr_(0), data_(NULL) {
+    itr.SetParam("buffer_size", "2");
+    itr.get_factory().Setup(source, nthread);
+    itr.Init();
+  }
+  virtual void BeforeFirst(void) {
+    itr.BeforeFirst();
+  }
+  virtual bool Next(void) {
+    if (at_end_) return false;
+    while (true) {
+      if (data_ == NULL || data_ptr_ >= data_->size()) {
+        if (!itr.Next(data_)) {
+          at_end_ = true; return false;
+        } else {
+          data_ptr_ = 0;
+        }
+      }
+      while (data_ptr_ < data_->size()) {
+        data_ptr_ += 1;
+        if ((*data_)[data_ptr_ - 1].Size() != 0) {
+          return true;
+        }
+      }
+    }
+    return true;
+  }
+  virtual const LibSVMPage &Value(void) const {
+    return (*data_)[data_ptr_ - 1];
+  }
+  inline size_t bytes_read(void) const {
+    return itr.get_factory().bytes_read();
+  }
+ private:
+  bool at_end_;
+  size_t data_ptr_;
+  std::vector<LibSVMPage> *data_;
+  utils::ThreadBuffer<std::vector<LibSVMPage>*, LibSVMPageFactory> itr;
+}; 
+
 }  // namespace io
 }  // namespace xgboost
 #endif  // XGBOOST_IO_LIBSVM_PARSER_H_