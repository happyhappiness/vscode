       * \return the index of instances paired
       */
      std::vector<int> GetPairs(int index) {
        utils::assert(index >= start_ && index < end_,"The query index out of sampling bound");
        return pairs_[index-start_];
      }

