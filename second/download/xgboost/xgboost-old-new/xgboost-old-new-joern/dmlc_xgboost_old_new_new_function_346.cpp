e<typename Sketch, typename RType>
inline void test(void) {
  Sketch sketch;
  size_t n;
  double wsum = 0.0;
  float eps, x, w;
  utils::Check(scanf("%lu%f", &n, &eps) == 2, "needs to start with n eps");
  sketch.Init(n, eps);
  printf("nlevel = %lu, limit_size=%lu\n", sketch.nlevel, sketch.limit_size);
  while (scanf("%f%f", &x, &w) == 2) {
    sketch.Push(x, static_cast<RType>(w));
    wsum += w;
  }
  sketch.CheckValid(static_cast<RType>(0.1));
  typename Sketch::SummaryContainer out;
  sketch.GetSummary(&out);
  double maxerr = static_cast<double>(out.MaxError());
  printf("MaxError=%g/%g = %g\n", maxerr, wsum, maxerr / wsum);
  out.Print();
}