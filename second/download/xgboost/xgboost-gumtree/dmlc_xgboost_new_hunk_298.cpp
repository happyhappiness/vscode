              src.size, maxsize, static_cast<double>(range),
              static_cast<double>(chunk));      
      for (size_t i = 0; i < src.size; ++i) {
        printf("[%lu] rmin=%g, rmax=%g, wmin=%g, v=%g, isbig=%d\n", i,
               src.data[i].rmin, src.data[i].rmax,  src.data[i].wmin,
               src.data[i].value, CheckLarge(src.data[i], chunk));
      }
      utils::Assert(nbig < n - 1, "quantile: too many large chunk");
    }
