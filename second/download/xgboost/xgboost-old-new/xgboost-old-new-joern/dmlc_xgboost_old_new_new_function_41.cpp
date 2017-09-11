inline void Push(bst_float fvalue, bst_float w, unsigned max_size) {
      if (next_goal == -1.0f) {
        next_goal = 0.0f;
        last_fvalue = fvalue;
        wmin = w;
        return;
      }
      if (last_fvalue != fvalue) {
        double rmax = rmin + wmin;
        if (rmax >= next_goal && sketch->temp.size != max_size) {
          if (sketch->temp.size == 0 ||
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
            next_goal = sum_total * 2.0f + 1e-5f;
          } else {
            next_goal = static_cast<bst_float>(sketch->temp.size * sum_total / max_size);
          }
        } else {
          if (rmax >= next_goal) {
            rabit::TrackerPrintf("INFO: rmax=%g, sum_total=%g, next_goal=%g, size=%lu\n",
                                 rmax, sum_total, next_goal, sketch->temp.size);
          }
        }
        rmin = rmax;
        wmin = w;
        last_fvalue = fvalue;
      } else {
        wmin += w;
      }
    }