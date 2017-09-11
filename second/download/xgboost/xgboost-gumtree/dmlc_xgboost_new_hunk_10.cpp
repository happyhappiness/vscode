};

struct EvalError : public EvalEWiseBase<EvalError> {
  explicit EvalError(const char* param) {
    if (param != nullptr) {
      std::ostringstream os;
      os << "error";
      CHECK_EQ(sscanf(param, "%f", &threshold_), 1)
        << "unable to parse the threshold value for the error metric";
      if (threshold_ != 0.5f) os << '@' << threshold_;
      name_ = os.str();
    } else {
      threshold_ = 0.5f;
      name_ = "error";
    }
  }
  const char *Name() const override {
    return name_.c_str();
  }
  inline float EvalRow(float label, float pred) const {
    // assume label is in [0,1]
    return pred > threshold_ ? 1.0f - label : label;
  }
 protected:
  float threshold_;
  std::string name_;
};

struct EvalPoissionNegLogLik : public EvalEWiseBase<EvalPoissionNegLogLik> {
  const char *Name() const override {
    return "poisson-nloglik";
  }
  inline float EvalRow(float y, float py) const {
    const float eps = 1e-16f;
    if (py < eps) py = eps;
    return common::LogGamma(y + 1.0f) + py - std::log(py) * y;
