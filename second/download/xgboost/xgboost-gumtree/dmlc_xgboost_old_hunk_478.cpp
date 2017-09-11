   * \param eps accuracy level of summary
   */
  inline void Init(RType maxn, double eps) {
    eps  = eps * 0.5;
    size_t L = 0;
    size_t b = std::max(floor(log2(eps * maxn) / eps), 8.0);
    // check for lower 
    while (b < maxn) {
      L = ceil(log2(maxn / b)) + 1;
      if (L < eps * b) break;
      ++b;
    }
    L += 1;
    inqueue.resize(b);
    level_batch = (b + 1) / 2 + 1;
    temp.Reserve(level_batch * 2);
    data.resize(level_batch * L);
    for (size_t l = 0; l < L; ++l) {
      Summary s; s.size = 0;
      s.data = BeginPtr(data) + l * level_batch;
      level.push_back(s);
    }
    qtail = 0;
  }
  /*! 
   * \brief add an element to a sketch 
   * \param x the elemented added to the sketch
   */
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
  /*! 
   * \brief finalize the result after all data has been passed 
   *        copy the final result to level 0
   *        this can only be called once
   */
  inline void Finalize(void) {
    // start update sketch
    std::sort(inqueue.begin(), inqueue.begin() + qtail);
    for (size_t i = 0; i < qtail; ++i) {
      temp.data[i] = Entry(i + 1, i + 1, inqueue[i]);
    }
    temp.size = static_cast<RType>(qtail);
    if (temp.size < level_batch) {
      level[0].CopyFrom(temp);
    } else {
      level[0].SetPrune(temp, level_batch);
    }
    // start adding other things in
    for (size_t l = 1; l < level.size(); ++l) {
      if (level[l].size == 0) continue;
      if (level[0].size == 0) {
        level[0].CopyFrom(level[l]);
      } else {
        temp.SetCombine(level[0], level[l]);
        level[0].SetPrune(temp, level_batch);        
      }
      level[l].size = 0;
    }
  }
  /*! \brief get the summary after finalize */
  inline Summary GetSummary(void) const {
    return level[0];
  }  
  
 private:  
  // the input queue
  std::vector<DType> inqueue;
  // end of the queue
  size_t qtail;
  // size of summary in each level
  size_t level_batch;
  // content of the summary
  std::vector<Entry> data;
  // different level of summary
  std::vector<Summary> level;  
  // temporal summary, used for temp-merge
  SummaryContainer temp;  
};

/*! 
 * \brief a helper class to compute streaming quantile
 * \tparam DType type of data content
 * \tparam RType type of rank
