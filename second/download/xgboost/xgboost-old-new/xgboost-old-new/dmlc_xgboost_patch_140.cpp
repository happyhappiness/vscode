@@ -8,6 +8,10 @@
 #include <cstdio>
 #include <string>
 #include <vector>
+#include <istream>
+#include <ostream>
+#include <streambuf>
+#include <cassert>
 
 /*! \brief namespace for dmlc */
 namespace dmlc {
@@ -38,7 +42,6 @@ class Stream {
    * \param uri the uri of the input currently we support
    *            hdfs://, s3://, and file:// by default file:// will be used
    * \param flag can be "w", "r", "a"
-   * \return a created stream
    */
   static Stream *Create(const char *uri, const char* const flag);
   // helper functions to write/read different data structures
@@ -103,11 +106,14 @@ class Serializable {
 class InputSplit {
  public:
   /*!
-   * \brief read next line, store into out_data
+   * \brief read next record, store into out_data
+   *   the data in outcomming record depends on the input data format
+   *   if input is text data, each line is returned as a record (\n not included)
+   *   if input is recordio, each record is returned
    * \param out_data the string that stores the line data, \n is not included
    * \return true of next line was found, false if we read all the lines
    */
-  virtual bool ReadLine(std::string *out_data) = 0;
+  virtual bool ReadRecord(std::string *out_data) = 0;
   /*! \brief destructor*/
   virtual ~InputSplit(void) {}  
   /*!
@@ -116,13 +122,133 @@ class InputSplit {
    * \param uri the uri of the input, can contain hdfs prefix
    * \param part_index the part id of current input
    * \param num_parts total number of splits
-   * \return a created input split
    */
   static InputSplit* Create(const char *uri,
                             unsigned part_index,
                             unsigned num_parts);
 };
 
+/*!
+ * \brief a std::ostream class that can can wrap Stream objects,
+ *  can use ostream with that output to underlying Stream
+ *
+ * Usage example:
+ * \code
+ *
+ *   Stream *fs = Stream::Create("hdfs:///test.txt", "w");
+ *   dmlc::ostream os(fs);
+ *   os << "hello world" << std::endl;
+ *   delete fs;
+ * \endcode
+ */
+class ostream : public std::basic_ostream<char> {
+ public:
+  /*!
+   * \brief construct std::ostream type
+   * \param stream the Stream output to be used
+   * \param buffer_size internal streambuf size
+   */
+  explicit ostream(Stream *stream,
+                   size_t buffer_size = 1 << 10)
+      : basic_ostream<char>(NULL), buf_(buffer_size) {
+    this->set_stream(stream);
+  }
+  // explictly synchronize the buffer
+  virtual ~ostream() {
+    buf_.pubsync();
+  }
+  /*!
+   * \brief set internal stream to be stream, reset states
+   * \param stream new stream as output
+   */
+  inline void set_stream(Stream *stream) {
+    buf_.set_stream(stream);
+    this->rdbuf(&buf_);
+  }
+  
+ private:
+  // internal streambuf
+  class OutBuf : public std::streambuf {
+   public:
+    explicit OutBuf(size_t buffer_size)
+        : stream_(NULL), buffer_(buffer_size) {
+      assert(buffer_.size() > 0); 
+    }
+    // set stream to the buffer
+    inline void set_stream(Stream *stream);
+    
+   private:
+    /*! \brief internal stream by StreamBuf */
+    Stream *stream_;
+    /*! \brief internal buffer */
+    std::vector<char> buffer_;
+    // override sync
+    inline int_type sync(void);
+    // override overflow
+    inline int_type overflow(int c);
+  };
+  /*! \brief buffer of the stream */
+  OutBuf buf_;
+};
+
+/*!
+ * \brief a std::istream class that can can wrap Stream objects,
+ *  can use istream with that output to underlying Stream
+ *
+ * Usage example:
+ * \code
+ *
+ *   Stream *fs = Stream::Create("hdfs:///test.txt", "r");
+ *   dmlc::istream is(fs);
+ *   is >> mydata;
+ *   delete fs;
+ * \endcode
+ */
+class istream : public std::basic_istream<char> {
+ public:
+  /*!
+   * \brief construct std::ostream type
+   * \param stream the Stream output to be used
+   * \param buffer_size internal buffer size
+   */
+  explicit istream(Stream *stream,
+                   size_t buffer_size = 1 << 10)                   
+      : basic_istream<char>(NULL), buf_(buffer_size) {
+    this->set_stream(stream);
+  }
+  virtual ~istream() {}
+  /*!
+   * \brief set internal stream to be stream, reset states
+   * \param stream new stream as output
+   */
+  inline void set_stream(Stream *stream) {
+    buf_.set_stream(stream);
+    this->rdbuf(&buf_);
+  }
+  
+ private:
+  // internal streambuf
+  class InBuf : public std::streambuf {
+   public:
+    explicit InBuf(size_t buffer_size)
+        : stream_(NULL), buffer_(buffer_size) {
+      assert(buffer_.size() > 0);
+    }
+    // set stream to the buffer
+    inline void set_stream(Stream *stream);
+    
+   private:
+    /*! \brief internal stream by StreamBuf */
+    Stream *stream_;
+    /*! \brief internal buffer */
+    std::vector<char> buffer_;
+    // override underflow
+    inline int_type underflow();
+  };
+  /*! \brief input buffer */
+  InBuf buf_;
+};
+
 // implementations of inline functions
 template<typename T>
 inline void Stream::Write(const std::vector<T> &vec) {
@@ -160,5 +286,48 @@ inline bool Stream::Read(std::string *out_str) {
   }
   return true;
 }
+
+// implementations for ostream
+inline void ostream::OutBuf::set_stream(Stream *stream) {
+  if (stream_ != NULL) this->pubsync();
+  this->stream_ = stream;
+  this->setp(&buffer_[0], &buffer_[0] + buffer_.size() - 1);
+}
+inline int ostream::OutBuf::sync(void) {
+  if (stream_ == NULL) return -1;
+  std::ptrdiff_t n = pptr() - pbase();
+  stream_->Write(pbase(), n);
+  this->pbump(-n);
+  return 0;
+}
+inline int ostream::OutBuf::overflow(int c) {
+  *(this->pptr()) = c;
+  std::ptrdiff_t n = pptr() - pbase();
+  this->pbump(-n);
+  if (c == EOF) {
+    stream_->Write(pbase(), n);
+  } else {
+    stream_->Write(pbase(), n + 1);
+  }
+  return c;
+}
+
+// implementations for istream
+inline void istream::InBuf::set_stream(Stream *stream) {
+  stream_ = stream;
+  this->setg(&buffer_[0], &buffer_[0], &buffer_[0]);  
+}
+inline int istream::InBuf::underflow() {
+  char *bhead = &buffer_[0];
+  if (this->gptr() == this->egptr()) {
+    size_t sz = stream_->Read(bhead, buffer_.size());
+    this->setg(bhead, bhead, bhead + sz);
+  }
+  if (this->gptr() == this->egptr()) {
+    return traits_type::eof();
+  } else {
+    return traits_type::to_int_type(*gptr());
+  }
+}
 }  // namespace dmlc
 #endif  // DMLC_IO_H_