              last_fvalue > sketch->temp.data[sketch->temp.size-1].value) {
            // push to sketch
            sketch->temp.data[sketch->temp.size] =
                common::WXQuantileSketch<bst_float, bst_float>::
                Entry(static_cast<bst_float>(rmin),
                      static_cast<bst_float>(rmax),
                      static_cast<bst_float>(wmin), last_fvalue);
            CHECK_LT(sketch->temp.size, max_size)
                << "invalid maximum size max_size=" << max_size
                << ", stemp.size" << sketch->temp.size;
            ++sketch->temp.size;
          }
          if (sketch->temp.size == max_size) {
