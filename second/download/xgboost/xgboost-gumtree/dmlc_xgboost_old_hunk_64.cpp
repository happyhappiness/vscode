          for (size_t i = 0; i < rowset.size(); ++i) {
            const bst_uint ridx = rowset[i];
            position[ridx] = root_index[ridx];
            utils::Assert(root_index[ridx] < (unsigned)tree.param.num_roots,
                          "root index exceed setting");
          }
        }
        // mark delete for the deleted datas
