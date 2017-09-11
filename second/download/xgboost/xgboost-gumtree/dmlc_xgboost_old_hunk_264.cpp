template<typename T>
inline bool CheckNAN(T v) {
#ifdef _MSC_VER
  return (_isnan(x) != 0);
#else
  return isnan(v);
#endif
}
template<typename T>
inline T LogGamma(T v) {
  return lgamma(v);
}
#endif
}  // namespace utils
