          }
          this->wspace.rptr.push_back(static_cast<unsigned>(this->wspace.cut.size()));
        } else {
          utils::Assert(offset == -2, "BUG in mark");
          bst_float cpt = feat_helper.MaxValue(fset[i]);
          this->wspace.cut.push_back(cpt + fabs(cpt) + rt_eps);
          this->wspace.rptr.push_back(static_cast<unsigned>(this->wspace.cut.size()));
