   public:
    explicit OutBuf(size_t buffer_size)
        : stream_(NULL), buffer_(buffer_size) {
      if (buffer_size == 0) buffer_.resize(2);
    }
    // set stream to the buffer
    inline void set_stream(Stream *stream);
