};

struct EvalError : public EvalEWiseBase<EvalError> {
  const char *Name() const override {
    return "error";
  }
  inline static float EvalRow(float label, float pred) {
    // assume label is in [0,1]
    return pred > 0.5f ? 1.0f - label : label;
  }
};

struct EvalPoissionNegLogLik : public EvalEWiseBase<EvalPoissionNegLogLik> {
  const char *Name() const override {
    return "poisson-nloglik";
  }
  inline static float EvalRow(float y, float py) {
    const float eps = 1e-16f;
    if (py < eps) py = eps;
    return common::LogGamma(y + 1.0f) + py - std::log(py) * y;
