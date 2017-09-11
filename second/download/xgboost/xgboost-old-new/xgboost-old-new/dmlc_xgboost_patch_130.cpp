@@ -11,7 +11,6 @@
 #include <istream>
 #include <ostream>
 #include <streambuf>
-#include <cassert>
 
 /*! \brief namespace for dmlc */
 namespace dmlc {
@@ -100,32 +99,71 @@ class Serializable {
 };
 
 /*!
- * \brief input split header, used to create input split on input dataset
- * this class can be used to obtain filesystem invariant splits from input files
+ * \brief input split creates that allows reading
+ *  of records from split of data,
+ *  independent part that covers all the dataset
+ * 
+ *  see InputSplit::Create for definition of record
  */
 class InputSplit {
  public:
+  /*! \brief a blob of memory region */
+  struct Blob {
+    /*! \brief points to start of the memory region */
+    void *dptr;
+    /*! \brief size of the memory region */
+    size_t size;
+  };
+  /*!
+   * \brief get the next record, the returning value
+   *   is valid until next call to NextRecord or NextChunk
+   *   caller can modify the memory content of out_rec
+   * \param out_rec used to store the result
+   * \return true if we can successfully get next record
+   *     false if we reached end of split
+   * \sa InputSplit::Create for definition of record
+   */
+  virtual bool NextRecord(Blob *out_rec) = 0;
   /*!
-   * \brief read next record, store into out_data
-   *   the data in outcomming record depends on the input data format
-   *   if input is text data, each line is returned as a record (\n not included)
-   *   if input is recordio, each record is returned
-   * \param out_data the string that stores the line data, \n is not included
-   * \return true of next line was found, false if we read all the lines
+   * \brief get a chunk of memory that can contain multiple records, 
+   *  the caller needs to parse the content of the resulting chunk,
+   *  for text file, out_chunk can contain data of multiple lines
+   *  for recordio, out_chunk can contain data of multiple records
+   *   
+   *  This function ensures there won't be partial record in the chunk
+   *  caller can modify the memory content of out_chunk,
+   *  the memory is valid until next call to NextRecord or NextChunk
+   *
+   *  Usually NextRecord is sufficient, NextChunk can be used by some
+   *  multi-threaded parsers to parse the input content
+   *
+   * \param out_chunk used to store the result
+   * \return true if we can successfully get next record
+   *     false if we reached end of split
+   * \sa InputSplit::Create for definition of record
    */
-  virtual bool ReadRecord(std::string *out_data) = 0;
+  virtual bool NextChunk(Blob *out_chunk) = 0;
   /*! \brief destructor*/
-  virtual ~InputSplit(void) {}  
+  virtual ~InputSplit(void) {}
   /*!
    * \brief factory function:
    *  create input split given a uri
    * \param uri the uri of the input, can contain hdfs prefix
    * \param part_index the part id of current input
    * \param num_parts total number of splits
+   * \param type type of record
+   *   List of possible types: "text", "recordio"
+   *     - "text":
+   *         text file, each line is treated as a record
+   *         input split will split on \n or \r
+   *     - "recordio":
+   *         binary recordio file, see recordio.h
+   * \sa InputSplit::Type
    */
   static InputSplit* Create(const char *uri,
                             unsigned part_index,
-                            unsigned num_parts);
+                            unsigned num_parts,
+                            const char *type);
 };
 
 /*!
@@ -172,7 +210,7 @@ class ostream : public std::basic_ostream<char> {
    public:
     explicit OutBuf(size_t buffer_size)
         : stream_(NULL), buffer_(buffer_size) {
-      assert(buffer_.size() > 0); 
+      if (buffer_size == 0) buffer_.resize(2);
     }
     // set stream to the buffer
     inline void set_stream(Stream *stream);
@@ -225,22 +263,32 @@ class istream : public std::basic_istream<char> {
     buf_.set_stream(stream);
     this->rdbuf(&buf_);
   }
-  
+  /*! \return how many bytes we read so far */
+  inline size_t bytes_read(void) const {
+    return buf_.bytes_read();
+  }
+
  private:
   // internal streambuf
   class InBuf : public std::streambuf {
    public:
     explicit InBuf(size_t buffer_size)
-        : stream_(NULL), buffer_(buffer_size) {
-      assert(buffer_.size() > 0);
+        : stream_(NULL), bytes_read_(0),
+          buffer_(buffer_size) {
+      if (buffer_size == 0) buffer_.resize(2);
     }
     // set stream to the buffer
     inline void set_stream(Stream *stream);
-    
+    // return how many bytes read so far
+    inline size_t bytes_read(void) const {
+      return bytes_read_;
+    }
    private:
     /*! \brief internal stream by StreamBuf */
     Stream *stream_;
-    /*! \brief internal buffer */
+    /*! \brief how many bytes we read so far */
+    size_t bytes_read_;
+    /*! \brief internal buffer */    
     std::vector<char> buffer_;
     // override underflow
     inline int_type underflow();
@@ -322,6 +370,7 @@ inline int istream::InBuf::underflow() {
   if (this->gptr() == this->egptr()) {
     size_t sz = stream_->Read(bhead, buffer_.size());
     this->setg(bhead, bhead, bhead + sz);
+    bytes_read_ += sz;
   }
   if (this->gptr() == this->egptr()) {
     return traits_type::eof();