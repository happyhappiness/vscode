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
