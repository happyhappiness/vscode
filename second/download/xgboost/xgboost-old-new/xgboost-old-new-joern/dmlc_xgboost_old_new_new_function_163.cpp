/*!
 *  Copyright (c) 2015 by Contributors
 * \file io.h
 * \brief defines serializable interface of dmlc
 */
#ifndef DMLC_IO_H_
#define DMLC_IO_H_
#include <cstdio>
#include <string>
#include <vector>
#include <istream>
#include <ostream>
#include <streambuf>

/*! \brief namespace for dmlc */
namespace dmlc {
/*!
 * \brief interface of stream I/O for serialization
 */
class Stream {
 public:
  /*!
   * \brief reads data from a stream
   * \param ptr pointer to a memory buffer
   * \param size block size
   * \return the size of data read
   */
  virtual size_t Read(void *ptr, size_t size) = 0;
  /*!
   * \brief writes data to a stream
   * \param ptr pointer to a memory buffer
   * \param size block size
   */
  virtual void Write(const void *ptr, size_t size) = 0;
  /*! \brief virtual destructor */
  virtual ~Stream(void) {}
  /*!
   * \brief generic factory function
   *    create an stream, the stream will close the underlying files
   *    upon deletion
   * \param uri the uri of the input currently we support
   *            hdfs://, s3://, and file:// by default file:// will be used
   * \param flag can be "w", "r", "a"
   */
  static Stream *Create(const char *uri, const char* const flag);
  // helper functions to write/read different data structures
  /*!
   * \brief writes a vector
   * \param vec vector to be written/serialized
   */
  template<typename T>
  inline void Write(const std::vector<T> &vec);
  /*!
   * \brief loads a vector
   * \param out_vec vector to be loaded/deserialized
   * \return whether the load was successful
   */
  template<typename T>
  inline bool Read(std::vector<T> *out_vec);
  /*!
   * \brief writes a string
   * \param str the string to be written/serialized
   */ 
  inline void Write(const std::string &str);
  /*!
   * \brief loads a string
   * \param out_str string to be loaded/deserialized
   * \return whether the load/deserialization was successful
   */
  inline bool Read(std::string *out_str);
};

/*! \brief interface of i/o stream that support seek */
class SeekStream: public Stream {
 public:
  // virtual destructor
  virtual ~SeekStream(void) {}
  /*! \brief seek to certain position of the file */
  virtual void Seek(size_t pos) = 0;
  /*! \brief tell the position of the stream */
  virtual size_t Tell(void) = 0;
  /*! \return whether we are at end of file */
  virtual bool AtEnd(void) const = 0;  
};

/*! \brief interface for serializable objects */
class Serializable {
 public:
  /*! 
  * \brief load the model from a stream
  * \param fi stream where to load the model from
  */
  virtual void Load(Stream *fi) = 0;
  /*! 
  * \brief saves the model to a stream
  * \param fo stream where to save the model to
  */
  virtual void Save(Stream *fo) const = 0;
};

/*!
 * \brief input split creates that allows reading
 *  of records from split of data,
 *  independent part that covers all the dataset
 * 
 *  see InputSplit::Create for definition of record
 */
class InputSplit {
 public:
  /*! \brief a blob of memory region */
  struct Blob {
    /*! \brief points to start of the memory region */
    void *dptr;
    /*! \brief size of the memory region */
    size_t size;
  };
  /*!
   * \brief get the next record, the returning value
   *   is valid until next call to NextRecord or NextChunk
   *   caller can modify the memory content of out_rec
   * \param out_rec used to store the result
   * \return true if we can successfully get next record
   *     false if we reached end of split
   * \sa InputSplit::Create for definition of record
   */
  virtual bool NextRecord(Blob *out_rec) = 0;
  /*!
   * \brief get a chunk of memory that can contain multiple records, 
   *  the caller needs to parse the content of the resulting chunk,
   *  for text file, out_chunk can contain data of multiple lines
   *  for recordio, out_chunk can contain data of multiple records
   *   
   *  This function ensures there won't be partial record in the chunk
   *  caller can modify the memory content of out_chunk,
   *  the memory is valid until next call to NextRecord or NextChunk
   *
   *  Usually NextRecord is sufficient, NextChunk can be used by some
   *  multi-threaded parsers to parse the input content
   *
   * \param out_chunk used to store the result
   * \return true if we can successfully get next record
   *     false if we reached end of split
   * \sa InputSplit::Create for definition of record
   */
  virtual bool NextChunk(Blob *out_chunk) = 0;
  /*! \brief destructor*/
  virtual ~InputSplit(void) {}
  /*!
   * \brief factory function:
   *  create input split given a uri
   * \param uri the uri of the input, can contain hdfs prefix
   * \param part_index the part id of current input
   * \param num_parts total number of splits
   * \param type type of record
   *   List of possible types: "text", "recordio"
   *     - "text":
   *         text file, each line is treated as a record
   *         input split will split on \n or \r
   *     - "recordio":
   *         binary recordio file, see recordio.h
   * \sa InputSplit::Type
   */
  static InputSplit* Create(const char *uri,
                            unsigned part_index,
                            unsigned num_parts,
                            const char *type);
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
      : std::basic_ostream<char>(NULL), buf_(buffer_size) {
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
      if (buffer_size == 0) buffer_.resize(2);
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
      : std::basic_istream<char>(NULL), buf_(buffer_size) {
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
  };
  /*! \brief input buffer */
  InBuf buf_;
};

// implementations of inline functions
template<typename T>
inline void Stream::Write(const std::vector<T> &vec) {
  size_t sz = vec.size();
  this->Write(&sz, sizeof(sz));
  if (sz != 0) {
    this->Write(&vec[0], sizeof(T) * sz);
  }
}
template<typename T>
inline bool Stream::Read(std::vector<T> *out_vec) {
  size_t sz;
  if (this->Read(&sz, sizeof(sz)) == 0) return false;
  out_vec->resize(sz);
  if (sz != 0) {
    if (this->Read(&(*out_vec)[0], sizeof(T) * sz) == 0) return false;
  }
  return true;
}
inline void Stream::Write(const std::string &str) {
  size_t sz = str.length();
  this->Write(&sz, sizeof(sz));
  if (sz != 0) {
    this->Write(&str[0], sizeof(char) * sz);
  }
}
inline bool Stream::Read(std::string *out_str) {
  size_t sz;
  if (this->Read(&sz, sizeof(sz)) == 0) return false;
  out_str->resize(sz);
  if (sz != 0) {
    if (this->Read(&(*out_str)[0], sizeof(char) * sz) == 0) {
      return false;
    }
  }
  return true;
}

// implementations for ostream
inline void ostream::OutBuf::set_stream(Stream *stream) {
  if (stream_ != NULL) this->pubsync();
  this->stream_ = stream;
  this->setp(&buffer_[0], &buffer_[0] + buffer_.size() - 1);
}
inline int ostream::OutBuf::sync(void) {
  if (stream_ == NULL) return -1;
  std::ptrdiff_t n = pptr() - pbase();
  stream_->Write(pbase(), n);
  this->pbump(-n);
  return 0;
}
inline int ostream::OutBuf::overflow(int c) {
  *(this->pptr()) = c;
  std::ptrdiff_t n = pptr() - pbase();
  this->pbump(-n);
  if (c == EOF) {
    stream_->Write(pbase(), n);
  } else {
    stream_->Write(pbase(), n + 1);
  }
  return c;
}

// implementations for istream
inline void istream::InBuf::set_stream(Stream *stream) {
  stream_ = stream;
  this->setg(&buffer_[0], &buffer_[0], &buffer_[0]);  
}
inline int istream::InBuf::underflow() {
  char *bhead = &buffer_[0];
  if (this->gptr() == this->egptr()) {
    size_t sz = stream_->Read(bhead, buffer_.size());
    this->setg(bhead, bhead, bhead + sz);
    bytes_read_ += sz;
  }
  if (this->gptr() == this->egptr()) {
    return traits_type::eof();
  } else {
    return traits_type::to_int_type(*gptr());
  }
}
}  // namespace dmlc
#endif  // DMLC_IO_H_
