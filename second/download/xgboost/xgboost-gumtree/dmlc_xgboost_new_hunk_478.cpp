   * \param eps accuracy level of summary
   */
  inline void Init(RType maxn, double eps) {
    nlevel = 0;
    size_t b = std::max(floor(log2(eps * maxn) / eps), 8.0);
    // check for small n case
    while (b < maxn) {
      nlevel = ceil(log2(maxn / b)) + 1;
      if (nlevel < eps * b) break;
      ++b;
    }
    nlevel += 1;
    level_batch = (b + 1) / 2 + 1;
    // lazy reserve the space, if there is only one value, no need to allocate space
    inqueue.resize(1);
    data.resize(0);
    level.resize(0);
    qtail = 0;
  }
  /*! 
   * \brief add an element to a sketch 
   * \param x the elemented added to the sketch
   */
  inline void Add(DType x, RType w = 1) {
    if (qtail == inqueue.size()) {
      // jump from lazy one value to level_batch * 2
      if (inqueue.size() == 1) {
        inqueue.resize(level_batch * 2);
      } else {
        temp.Reserve(2 * level_batch);
        this->Queue2Summary(&temp);
        for (size_t l = 1; true; ++l) {
          this->InitLevel(std::max(l + 1, nlevel));
          // check if level l is empty
          if (level[l].size == 0) {
            level[l].SetPrune(temp, level_batch); break;            
          } else {
            // level 0 is actually temp space
            level[0].SetPrune(temp, level_batch);
            temp.SetCombine(level[0], level[l]);
            if (temp.size > level_batch) {
              // try next level
              level[l].size = 0;
            } else {
              // if merged record is still smaller, no need to send to next level
              level[l].CopyFrom(temp); break;
            }
          }
        }
      }
    }
    if (qtail == 0 || inqueue[qtail - 1].value != x) {
      inqueue[qtail++] = QEntry(x, w); 
    } else {
      inqueue[qtail - 1].weight += w;
    }
  } 
  /*! \brief get the summary after finalize */
  inline void GetSummary(SummaryContainer *out) {
    if (level.size() != 0) {
      out->Reserve(level_batch * 2);
    }
    this->Queue2Summary(out);
    if (level.size() != 0) {
      level[0].SetPrune(*out, level_batch);
      for (size_t l = 1; l < level.size(); ++l) {
        if (level[l].size == 0) continue;
        if (level[0].size == 0) {
          level[0].CopyFrom(level[l]);
        } else {
          out->SetCombine(level[0], level[l]);
          level[0].SetPrune(*out, level_batch);
        }
      }
      out->CopyFrom(level[0]);
    }
  }
  
 private:
  // initialize level space to at least nlevel
  inline void InitLevel(size_t nlevel) {
    if (level.size() >= nlevel) return;
    data.resize(level_batch * nlevel);
    level.resize(nlevel, Summary());
    for (size_t l = 0; l < level.size(); ++l) {
      level[l].data = BeginPtr(data) + l * level_batch;
    }
  }
  inline void Queue2Summary(SummaryContainer *temp) {
    // reserve temp space
    temp->Reserve(inqueue.size());
    temp->size = 0;
    // start update sketch
    std::sort(inqueue.begin(), inqueue.begin() + qtail);
    RType wsum = 0;
    // construct data with unique weights
    for (size_t i = 0; i < qtail;) {
      size_t j = 1;
      RType w = inqueue[i].weight;
      while (j < qtail && inqueue[j].value == inqueue[i].value) {
        w += inqueue[j].weight; ++j;
      }
      temp->data[temp->size++] = Entry(wsum, wsum + w, w, inqueue[i].value);
      wsum += w; i = j;
    }
    // clean up queue
    qtail = 0;
  }
  // entry in the queue
  struct QEntry {
    // value of the instance
    DType value;
    // weight of instance
    RType weight;
    // default constructor
    QEntry(void) {}
    // constructor
    QEntry(DType value, RType weight) 
        : value(value), weight(weight) {}
    // comparator on value
    inline bool operator<(const QEntry &b) const {
      return value < b.value;
    }
  };
  // the input queue
  std::vector<QEntry> inqueue;
  // end of the queue
  size_t qtail;
  // number of levels
  size_t nlevel;
  // size of summary in each level
  size_t level_batch;
  // the level of each summaries
  std::vector<Summary> level;
  // content of the summary
  std::vector<Entry> data;
  // temporal summary, used for temp-merge
  SummaryContainer temp;  
};

/*!
 * \brief a helper class to compute streaming quantile
 * \tparam DType type of data content
 * \tparam RType type of rank
