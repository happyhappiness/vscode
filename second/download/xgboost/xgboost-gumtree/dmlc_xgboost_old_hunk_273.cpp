   public:
    explicit OutBuf(size_t buffer_size)
        : stream_(NULL), buffer_(buffer_size) {
      assert(buffer_.size() > 0); 
    }
    // set stream to the buffer
    inline void set_stream(Stream *stream);
