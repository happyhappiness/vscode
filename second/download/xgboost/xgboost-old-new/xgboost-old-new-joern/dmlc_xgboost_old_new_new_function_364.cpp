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