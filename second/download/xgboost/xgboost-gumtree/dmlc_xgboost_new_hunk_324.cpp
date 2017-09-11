#include <string>
#include <cstring>
#include "./utils.h"
#include "../sync/sync.h"
/*!
 * \file io.h
 * \brief general stream interface for serialization, I/O
 * \author Tianqi Chen
 */
namespace xgboost {
namespace utils {
// reuse the definitions of streams
typedef rabit::IStream IStream;
typedef rabit::utils::ISeekStream ISeekStream;
typedef rabit::utils::MemoryFixSizeBuffer MemoryFixSizeBuffer;
typedef rabit::utils::MemoryBufferStream MemoryBufferStream;
typedef rabit::io::Base64InStream Base64InStream;
typedef rabit::io::Base64OutStream Base64OutStream;

/*! \brief implementation of file i/o stream */
class FileStream : public ISeekStream {
