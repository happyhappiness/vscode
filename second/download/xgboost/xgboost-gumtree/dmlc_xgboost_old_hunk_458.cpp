  virtual size_t Tell(void) = 0;
};

/*! \brief a in memory buffer that can be read and write as stream interface */
struct MemoryBufferStream : public ISeekStream {
 public:
