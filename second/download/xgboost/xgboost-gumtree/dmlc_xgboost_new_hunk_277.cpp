    buf_.set_stream(stream);
    this->rdbuf(&buf_);
  }
  /*! \return how many bytes we read so far */
  inline size_t bytes_read(void) const {
    return buf_.bytes_read();
  }

 private:
  // internal streambuf
  class InBuf : public std::streambuf {
   public:
    explicit InBuf(size_t buffer_size)
        : stream_(NULL), bytes_read_(0),
          buffer_(buffer_size) {
      if (buffer_size == 0) buffer_.resize(2);
    }
    // set stream to the buffer
    inline void set_stream(Stream *stream);
    // return how many bytes read so far
    inline size_t bytes_read(void) const {
      return bytes_read_;
    }
   private:
    /*! \brief internal stream by StreamBuf */
    Stream *stream_;
    /*! \brief how many bytes we read so far */
    size_t bytes_read_;
    /*! \brief internal buffer */    
    std::vector<char> buffer_;
    // override underflow
    inline int_type underflow();
