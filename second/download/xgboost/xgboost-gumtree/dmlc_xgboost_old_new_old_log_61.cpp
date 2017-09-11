utils::Assert(nodes[nodes[rid].cright()].is_leaf(),
                  "can not delete a non termial child");