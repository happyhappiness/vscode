      this->wspace.cut.push_back(0.0f);
      this->wspace.rptr.push_back(static_cast<unsigned>(this->wspace.cut.size()));
    }
    utils::Assert(this->wspace.rptr.size() ==
                  (fset.size() + 1) * this->qexpand.size() + 1,
                  "cut space inconsistent");
  }

 private:
  inline void UpdateHistCol(const std::vector<bst_gpair> &gpair,
                            const ColBatch::Inst &c,
                            const BoosterInfo &info,
                            const RegTree &tree,
                            const std::vector<bst_uint> &fset,
                            bst_uint fid_offset,
