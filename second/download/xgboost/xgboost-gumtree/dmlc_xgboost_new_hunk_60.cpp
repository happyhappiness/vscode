      this->wspace.cut.push_back(0.0f);
      this->wspace.rptr.push_back(this->wspace.cut.size());
    }
    CHECK_EQ(this->wspace.rptr.size(),
             (tree.param.num_feature + 1) * this->qexpand.size() + 1);
  }

 private:
