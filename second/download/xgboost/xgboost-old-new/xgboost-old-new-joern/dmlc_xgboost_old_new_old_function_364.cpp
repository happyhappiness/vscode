inline void Add(DType x) {
    inqueue[qtail++] = x;
    if (qtail == inqueue.size()) {
      // start update sketch
      std::sort(inqueue.begin(), inqueue.end());
      for (size_t i = 0; i < qtail; ++i) {
        temp.data[i] = Entry(i + 1, i + 1, inqueue[i]);
      }
      temp.size = static_cast<RType>(qtail);
      // clean up queue
      qtail = 0;
      for (size_t l = 1; l < level.size(); ++l) {
        // check if level l is empty
        if (level[l].size == 0) {
          level[l].SetPrune(temp, level_batch);
          return;
        } else {
          // level 0 is actually temp space
          level[0].SetPrune(temp, level_batch);
          temp.SetCombine(level[0], level[l]);
          level[l].size = 0;
        }
      }
      utils::Error("adding more element than allowed");
    }
  }