        }
      }
      for (size_t i = 0; i < sketchs.size(); ++i) {
        common::WXQuantileSketch<bst_float, bst_float>::SummaryContainer out;
        sketchs[i].GetSummary(&out);
        summary_array[i].SetPrune(out, max_size);
      }
      CHECK_EQ(summary_array.size(), sketchs.size());
    };
    if (summary_array.size() != 0) {
      size_t nbytes = WXQSketch::SummaryContainer::CalcMemCost(max_size);
#if __cplusplus >= 201103L
      sreducer.Allreduce(dmlc::BeginPtr(summary_array),
                         nbytes, summary_array.size(), lazy_get_summary);
#else
      sreducer.Allreduce(dmlc::BeginPtr(summary_array), nbytes, summary_array.size());
#endif
    }
    // now we get the final result of sketch, setup the cut
