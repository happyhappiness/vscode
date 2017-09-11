    inline void Finalize(unsigned max_size) {
      double rmax = rmin + wmin;
      if (sketch->temp.size == 0 || last_fvalue > sketch->temp.data[sketch->temp.size-1].value) {
        CHECK_LE(sketch->temp.size, max_size)
            << "Finalize: invalid maximum size, max_size=" << max_size
            << ", stemp.size=" << sketch->temp.size;
        // push to sketch
        sketch->temp.data[sketch->temp.size] =
            common::WXQuantileSketch<bst_float, bst_float>::
            Entry(static_cast<bst_float>(rmin),
                  static_cast<bst_float>(rmax),
                  static_cast<bst_float>(wmin), last_fvalue);
