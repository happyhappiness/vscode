utils::Assert(static_cast<int>(deleted_nodes.size()) == param.num_deleted,
                  "number of deleted nodes do not match, num_deleted=%d, dnsize=%lu, num_nodes=%d",
                  param.num_deleted, deleted_nodes.size(), param.num_nodes);