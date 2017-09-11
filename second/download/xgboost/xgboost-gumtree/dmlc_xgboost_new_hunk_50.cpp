      } else {
        for (size_t i = 0; i < position.size(); ++i) {
          position[i] = root_index[i];
          CHECK_LT(root_index[i], (unsigned)tree.param.num_roots)
              << "root index exceed setting";
        }
      }
      // mark delete for the deleted datas
