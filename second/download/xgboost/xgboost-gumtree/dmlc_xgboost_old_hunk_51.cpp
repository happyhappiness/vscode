              last_fvalue > sketch->temp.data[sketch->temp.size-1].value) {
            // push to sketch
            sketch->temp.data[sketch->temp.size] =
                utils::WXQuantileSketch<bst_float, bst_float>::
                Entry(static_cast<bst_float>(rmin),
                      static_cast<bst_float>(rmax),
                      static_cast<bst_float>(wmin), last_fvalue);
            utils::Assert(sketch->temp.size < max_size,
                          "invalid maximum size max_size=%u, stemp.size=%lu\n",
                          max_size, sketch->temp.size);
            ++sketch->temp.size;
          }
          if (sketch->temp.size == max_size) {
