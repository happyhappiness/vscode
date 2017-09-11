  typename Sketch::SummaryContainer out;
  sketch.GetSummary(&out);
  double maxerr = static_cast<double>(out.MaxError());
  out.Print();
  
  printf("MaxError=%g/%g = %g\n", maxerr, wsum, maxerr / wsum);
  printf("maxlevel = %lu, usedlevel=%lu, limit_size=%lu\n", sketch.nlevel, sketch.level.size(), sketch.limit_size);
}

int main(int argc, char *argv[]) {
