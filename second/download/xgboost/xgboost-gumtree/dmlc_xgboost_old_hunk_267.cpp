
namespace xgboost {
namespace utils {
class SingleFileSplit : public dmlc::InputSplit {
 public:
  explicit SingleFileSplit(const char *fname) 
      : use_stdin_(false) {
    if (!std::strcmp(fname, "stdin")) {
#ifndef XGBOOST_STRICT_CXX98_
      use_stdin_ = true; fp_ = stdin;
#endif
    }
    if (!use_stdin_) {
      fp_ = utils::FopenCheck(fname, "r");
    }
    end_of_file_ = false;
  }
  virtual ~SingleFileSplit(void) {
    if (!use_stdin_) std::fclose(fp_);
  }
  virtual bool ReadRecord(std::string *out_data) {
    if (end_of_file_) return false;
    out_data->clear();
    while (true) {
      char c = std::fgetc(fp_);
      if (c == EOF) {
        end_of_file_ = true;
      }
      if (c != '\r' && c != '\n' && c != EOF) {
        *out_data += c;
      } else {
        if (out_data->length() != 0) return true;
        if (end_of_file_) return false;
      }
    }
    return false;
  }  
    
 private:
  std::FILE *fp_;
  bool use_stdin_;
  bool end_of_file_;
};

class StdFile : public dmlc::Stream {
