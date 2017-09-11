  typename Sketch::SummaryContainer out;
  sketch.GetSummary(&out);
  double maxerr = static_cast<double>(out.MaxError());
  printf("MaxError=%g/%g = %g\n", maxerr, wsum, maxerr / wsum);
  out.Print();
}

int main(int argc, char *argv[]) {
