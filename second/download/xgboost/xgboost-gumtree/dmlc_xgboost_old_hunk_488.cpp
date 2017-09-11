class ISeekStream: public IStream {
 public:
  /*! \brief seek to certain position of the file */
  virtual void Seek(long pos) = 0;
  /*! \brief tell the position of the stream */
  virtual long Tell(void) = 0;
};

/*! \brief implementation of file i/o stream */
class FileStream : public ISeekStream {
 public:
