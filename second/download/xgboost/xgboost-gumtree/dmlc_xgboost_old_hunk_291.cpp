  std::vector<float> labels;
};

// dense matrix
struct Matrix {
  inline void Init(size_t nrow, size_t ncol, float v = 0.0f) {
    this->nrow = nrow;
    this->ncol = ncol;
    data.resize(nrow * ncol);
    std::fill(data.begin(), data.end(), v);
  }
  inline float *operator[](size_t i) {
    return &data[0] + i * ncol;
  }
  inline const float *operator[](size_t i) const {
    return &data[0] + i * ncol;
  }
  inline void Print(const char *fname) {
    FILE *fo;
    if (!strcmp(fname, "stdout")) {
      fo = stdout;
    } else {
      fo = utils::FopenCheck(fname, "w");
    }
    for (size_t i = 0; i < data.size(); ++i) {
      fprintf(fo, "%g", data[i]);
      if ((i+1) % ncol == 0) {
        fprintf(fo, "\n");
      } else {
        fprintf(fo, " ");
      }
    }
    // close the filed
    if (fo != stdout) fclose(fo);
  }
  // number of data
  size_t nrow, ncol;
  std::vector<float> data;
};

/*!\brief computes a random number modulo the value */
inline int Random(int value) {
  return rand() % value;
