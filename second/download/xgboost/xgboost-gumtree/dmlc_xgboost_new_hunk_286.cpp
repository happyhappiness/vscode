   * \param uri the uri of the input, can contain hdfs prefix
   * \param part_index the part id of current input
   * \param num_parts total number of splits
   */
  static InputSplit* Create(const char *uri,
                            unsigned part_index,
                            unsigned num_parts);
};

/*!
 * \brief a std::ostream class that can can wrap Stream objects,
 *  can use ostream with that output to underlying Stream
 *
 * Usage example:
 * \code
 *
 *   Stream *fs = Stream::Create("hdfs:///test.txt", "w");
 *   dmlc::ostream os(fs);
 *   os << "hello world" << std::endl;
 *   delete fs;
 * \endcode
 */
class ostream : public std::basic_ostream<char> {
 public:
  /*!
   * \brief construct std::ostream type
   * \param stream the Stream output to be used
   * \param buffer_size internal streambuf size
   */
  explicit ostream(Stream *stream,
                   size_t buffer_size = 1 << 10)
      : basic_ostream<char>(NULL), buf_(buffer_size) {
    this->set_stream(stream);
  }
  // explictly synchronize the buffer
  virtual ~ostream() {
    buf_.pubsync();
  }
  /*!
   * \brief set internal stream to be stream, reset states
   * \param stream new stream as output
   */
  inline void set_stream(Stream *stream) {
    buf_.set_stream(stream);
    this->rdbuf(&buf_);
  }
  
 private:
  // internal streambuf
  class OutBuf : public std::streambuf {
   public:
    explicit OutBuf(size_t buffer_size)
        : stream_(NULL), buffer_(buffer_size) {
      assert(buffer_.size() > 0); 
    }
    // set stream to the buffer
    inline void set_stream(Stream *stream);
    
   private:
    /*! \brief internal stream by StreamBuf */
    Stream *stream_;
    /*! \brief internal buffer */
    std::vector<char> buffer_;
    // override sync
    inline int_type sync(void);
    // override overflow
    inline int_type overflow(int c);
  };
  /*! \brief buffer of the stream */
  OutBuf buf_;
};

/*!
 * \brief a std::istream class that can can wrap Stream objects,
 *  can use istream with that output to underlying Stream
 *
 * Usage example:
 * \code
 *
 *   Stream *fs = Stream::Create("hdfs:///test.txt", "r");
 *   dmlc::istream is(fs);
 *   is >> mydata;
 *   delete fs;
 * \endcode
 */
class istream : public std::basic_istream<char> {
 public:
  /*!
   * \brief construct std::ostream type
   * \param stream the Stream output to be used
   * \param buffer_size internal buffer size
   */
  explicit istream(Stream *stream,
                   size_t buffer_size = 1 << 10)                   
      : basic_istream<char>(NULL), buf_(buffer_size) {
    this->set_stream(stream);
  }
  virtual ~istream() {}
  /*!
   * \brief set internal stream to be stream, reset states
   * \param stream new stream as output
   */
  inline void set_stream(Stream *stream) {
    buf_.set_stream(stream);
    this->rdbuf(&buf_);
  }
  
 private:
  // internal streambuf
  class InBuf : public std::streambuf {
   public:
    explicit InBuf(size_t buffer_size)
        : stream_(NULL), buffer_(buffer_size) {
      assert(buffer_.size() > 0);
    }
    // set stream to the buffer
    inline void set_stream(Stream *stream);
    
   private:
    /*! \brief internal stream by StreamBuf */
    Stream *stream_;
    /*! \brief internal buffer */
    std::vector<char> buffer_;
    // override underflow
    inline int_type underflow();
  };
  /*! \brief input buffer */
  InBuf buf_;
};

// implementations of inline functions
template<typename T>
inline void Stream::Write(const std::vector<T> &vec) {
