@@ -22,7 +22,7 @@ namespace io {
 /*! \brief page returned by libsvm parser */
 struct LibSVMPage : public SparsePage {
   std::vector<float> label;
-  // overload clear  
+  // overload clear
   inline void Clear() {
     SparsePage::Clear();
     label.clear();
@@ -35,7 +35,7 @@ struct LibSVMPage : public SparsePage {
  */
 class LibSVMPageFactory  {
  public:
-  explicit LibSVMPageFactory() 
+  LibSVMPageFactory()
       : bytes_read_(0), at_head_(true) {
   }
   inline bool Init(void) {
@@ -85,7 +85,7 @@ class LibSVMPageFactory  {
     data->resize(nthread);
     bytes_read_ += chunk.size;
     utils::Assert(chunk.size != 0, "LibSVMParser.FileData");
-    char *head = reinterpret_cast<char*>(chunk.dptr);        
+    char *head = reinterpret_cast<char*>(chunk.dptr);
     #pragma omp parallel num_threads(nthread_)
     {
       // threadid
@@ -150,7 +150,7 @@ class LibSVMPageFactory  {
     }
     return begin;
   }
-  
+
  private:
   // nthread
   int nthread_;
@@ -199,12 +199,13 @@ class LibSVMParser : public utils::IIterator<LibSVMPage> {
   inline size_t bytes_read(void) const {
     return itr.get_factory().bytes_read();
   }
+
  private:
   bool at_end_;
   size_t data_ptr_;
   std::vector<LibSVMPage> *data_;
   utils::ThreadBuffer<std::vector<LibSVMPage>*, LibSVMPageFactory> itr;
-}; 
+};
 
 }  // namespace io
 }  // namespace xgboost