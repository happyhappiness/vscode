#if _MSC_VER >= 1800
  return lgamma(v);
#else
#pragma message("Warning: lgamma function was not available until VS2013"\
                ", poisson regression will be disabled")
  utils::Error("lgamma function was not available until VS2013");
  return static_cast<T>(1.0);
#endif
