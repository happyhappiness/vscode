  }
  virtual void Save(Stream *fo) const {
    utils::Error("not implemented");
  }
};
struct WriteWrapper : public Serializable {
  const char *data;
