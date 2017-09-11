      } else {
        for (size_t i = 0; i < position.size(); ++i) {
          position[i] = root_index[i];
          utils::Assert(root_index[i] < (unsigned)tree.param.num_roots,
                        "root index exceed setting");
        }
      }
      // mark delete for the deleted datas
