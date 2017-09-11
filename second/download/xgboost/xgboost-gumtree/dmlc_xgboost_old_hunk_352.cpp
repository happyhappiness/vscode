  }
};

/*! \brief implementation of file i/o stream */
class FileStream : public IStream {
 private:
  std::FILE *fp;
 public:
  explicit FileStream(std::FILE *fp) : fp(fp) {
  }
  virtual size_t Read(void *ptr, size_t size) {
    return std::fread(ptr, size, 1, fp);
  }
  virtual void Write(const void *ptr, size_t size) {
    std::fwrite(ptr, size, 1, fp);
  }
  inline void Seek(size_t pos) {
    std::fseek(fp, 0, SEEK_SET);
  }
  inline void Close(void) {
    std::fclose(fp);
  }
};

}  // namespace utils
}  // namespace xgboost
#endif
