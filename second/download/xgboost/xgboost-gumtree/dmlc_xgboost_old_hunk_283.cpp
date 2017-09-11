  virtual void InitAfterException(void) {
    utils::Error("EmptyEngine is not fault tolerant");
  }
  virtual int LoadCheckPoint(ISerializable *global_model,
                             ISerializable *local_model = NULL) {
    return 0;
  }
  virtual void CheckPoint(const ISerializable *global_model,
                          const ISerializable *local_model = NULL) {
    version_number += 1;
  }
  virtual void LazyCheckPoint(const ISerializable *global_model) {
    version_number += 1;
  }
  virtual int VersionNumber(void) const {
