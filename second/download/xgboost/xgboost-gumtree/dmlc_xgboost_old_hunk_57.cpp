        }
      }
      for (size_t i = 0; i < sketchs.size(); ++i) {
        utils::WXQuantileSketch<bst_float, bst_float>::SummaryContainer out;
        sketchs[i].GetSummary(&out);
        summary_array[i].SetPrune(out, max_size);
      }
      utils::Assert(summary_array.size() == sketchs.size(), "shape mismatch");
    };
    if (summary_array.size() != 0) {
      size_t nbytes = WXQSketch::SummaryContainer::CalcMemCost(max_size);
#if __cplusplus >= 201103L
      sreducer.Allreduce(BeginPtr(summary_array), nbytes, summary_array.size(), lazy_get_summary);
#else
      sreducer.Allreduce(BeginPtr(summary_array), nbytes, summary_array.size());
#endif
    }
    // now we get the final result of sketch, setup the cut
