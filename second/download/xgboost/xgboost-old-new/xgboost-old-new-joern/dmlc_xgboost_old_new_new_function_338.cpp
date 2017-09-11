e<typename Summary>
inline void verifyWQ(std::vector<Entry> &dat, Summary out) {
 MakeQuantile(dat);
 size_t j = 0;
 double err = 0.0;
 const double eps = 1e-4;
 for (size_t i = 0; i < out.size; ++i) {
   while (j < dat.size() && dat[j].x < out.data[i].value) ++j;
   utils::Assert(j < dat.size() && fabs(dat[j].x - out.data[i].value) < eps, "bug");
   err = std::min(dat[j].rmin - out.data[i].rmin, err);
   err = std::min(out.data[i].rmax - dat[j].rmin + dat[j].w, err);
   err = std::min(dat[j].w - out.data[i].wmin, err);
 }
 if (err < 0.0) err = -err;
 printf("verify correctness, max-constraint-violation=%g (0 means perfect, coubld be nonzero due to floating point)\n", err);
}