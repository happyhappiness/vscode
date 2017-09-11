@@ -11,6 +11,10 @@
 #include "../utils/io.h"
 #include <string>
 
+namespace MPI {
+// forward delcaration of MPI::Datatype, but not include content
+class Datatype;
+};
 namespace xgboost {
 /*! \brief syncrhonizer module that minimumly wraps interface of MPI */
 namespace sync {
@@ -62,23 +66,31 @@ void Bcast(std::string *sendrecv_data, int root);
 class ReduceHandle {
  public:
   // reduce function
-  typedef void (ReduceFunction) (const void *src, void *dst, int len);
+  typedef void (ReduceFunction) (const void *src, void *dst, int len, const MPI::Datatype &dtype);
   // constructor
   ReduceHandle(void);
   // destructor
   ~ReduceHandle(void);
-  // initialize the reduce function
-  void Init(ReduceFunction redfunc, bool commute = true);
+  /*!
+   * \brief initialize the reduce function, with the type the reduce function need to deal with   
+   */
+  void Init(ReduceFunction redfunc, size_t type_n4bytes, bool commute = true);
   /*!
    * \brief customized in-place all reduce operation 
    * \param sendrecvbuf the in place send-recv buffer
-   * \param n4bytes number of nbytes send through all reduce
+   * \param type_n4bytes unit size of the type, in terms of 4bytes
+   * \param count number of elements to send
    */
-  void AllReduce(void *sendrecvbuf, size_t n4bytes);
-  
+  void AllReduce(void *sendrecvbuf, size_t type_n4bytes, size_t count);
+  /*! \return the number of bytes occupied by the type */
+  static int TypeSize(const MPI::Datatype &dtype);
  private:
   // handle data field
   void *handle;
+  // handle to the type field
+  void *htype;
+  // the created type in 4 bytes
+  size_t created_type_n4bytes;
 };
 
 // ----- extensions for ease of use ------
@@ -92,7 +104,7 @@ template<typename DType>
 class Reducer {
  public:
   Reducer(void) {
-    handle.Init(ReduceInner);
+    handle.Init(ReduceInner, kUnit);
     utils::Assert(sizeof(DType) % sizeof(int) == 0, "struct must be multiple of int");
   }
   /*!
@@ -102,24 +114,23 @@ class Reducer {
    * \param reducer the reducer function
    */
   inline void AllReduce(DType *sendrecvbuf, size_t count) {
-    handle.AllReduce(sendrecvbuf, count * kUnit);
+    handle.AllReduce(sendrecvbuf, kUnit, count);
   }
 
  private:
   // unit size 
   static const size_t kUnit = sizeof(DType) / sizeof(int);
   // inner implementation of reducer
-  inline static void ReduceInner(const void *src_, void *dst_, int len_) {
+  inline static void ReduceInner(const void *src_, void *dst_, int len_, const MPI::Datatype &dtype) {
     const int *psrc = reinterpret_cast<const int*>(src_);
     int *pdst = reinterpret_cast<int*>(dst_);
     DType tdst, tsrc;
-    utils::Assert(len_ % kUnit == 0, "length not divide by size");
-    for (size_t i = 0; i < len_; i += kUnit) {
+    for (size_t i = 0; i < len_; ++i) {
       // use memcpy to avoid alignment issue
-      std::memcpy(&tdst, pdst + i, sizeof(tdst));
-      std::memcpy(&tsrc, psrc + i, sizeof(tsrc));
+      std::memcpy(&tdst, pdst + i * kUnit, sizeof(tdst));
+      std::memcpy(&tsrc, psrc + i * kUnit, sizeof(tsrc));
       tdst.Reduce(tsrc);
-      std::memcpy(pdst + i, &tdst, sizeof(tdst));      
+      std::memcpy(pdst + i * kUnit, &tdst, sizeof(tdst));      
     }
   }
   // function handle
@@ -135,38 +146,47 @@ class Reducer {
  *   (1) Save(IStream &fs)  (2) Load(IStream &fs) (3) Reduce(const DType &d);
  */
 template<typename DType>
-class ComplexReducer {
+class SerializeReducer {
  public:
-  ComplexReducer(void) {
-    handle.Init(ReduceInner);
+  SerializeReducer(void) {
+    handle.Init(ReduceInner, 0);
   }
   /*!
-   * \brief customized in-place all reduce operation 
+   * \brief customized in-place all reduce operation
    * \param sendrecvobj pointer to the object to be reduced
    * \param max_n4byte maximum amount of memory needed in 4byte
    * \param reducer the reducer function
    */
-  inline void AllReduce(DType *sendrecvobj, size_t max_n4byte) {
-    buffer.resize(max_n4byte);
-    utils::MemoryFixSizeBuffer fs(BeginPtr(buffer), max_n4byte * 4);
-    sendrecvobj->Save(fs);
-    handle.AllReduce(BeginPtr(buffer), max_n4byte);
-    fs.Seek(0);
-    sendrecvobj->Load(fs);
+  inline void AllReduce(DType *sendrecvobj, size_t max_n4byte, size_t count) {
+    buffer.resize(max_n4byte * count);
+    for (size_t i = 0; i < count; ++i) {
+      utils::MemoryFixSizeBuffer fs(BeginPtr(buffer) + i * max_n4byte * 4, max_n4byte * 4);
+      sendrecvobj[i]->Save(fs);
+    }
+    handle.AllReduce(BeginPtr(buffer), max_n4byte, count);
+    for (size_t i = 0; i < count; ++i) {
+      utils::MemoryFixSizeBuffer fs(BeginPtr(buffer) + i * max_n4byte * 4, max_n4byte * 4);
+      sendrecvobj[i]->Load(fs);
+    }
   }
 
  private:
   // unit size
   // inner implementation of reducer
-  inline static void ReduceInner(const void *src_, void *dst_, int len_) {
-    utils::MemoryFixSizeBuffer fsrc((void*)(src_), len_);
-    utils::MemoryFixSizeBuffer fdst(dst_, len_);
+  inline static void ReduceInner(const void *src_, void *dst_, int len_, const MPI::Datatype &dtype) {
+    int nbytes = ReduceHandle::TypeSize(dtype);
     // temp space
     DType tsrc, tdst;
-    tsrc.Load(fsrc); tdst.Load(fdst);
-    // govern const check
-    tdst.Reduce(static_cast<const DType &>(tsrc));
-    tdst.Save(fdst);
+    for (int i = 0; i < len_; ++i) {
+      utils::MemoryFixSizeBuffer fsrc((void*)(src_) + i * nbytes, nbytes);
+      utils::MemoryFixSizeBuffer fdst(dst_ + i * nbytes, nbytes);
+      tsrc.Load(fsrc);
+      tdst.Load(fdst);
+      // govern const check
+      tdst.Reduce(static_cast<const DType &>(tsrc));
+      fdst.Seek(0);
+      tdst.Save(fdst);
+    }
   }
   // function handle
   ReduceHandle handle;