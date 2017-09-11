inline void ChangeToLeaf(int rid, float value) {
    utils::Assert(nodes[nodes[rid].cleft() ].is_leaf(),
                  "can not delete a non termial child");
    utils::Assert(nodes[nodes[rid].cright()].is_leaf(),
                  "can not delete a non termial child");
    this->DeleteNode(nodes[rid].cleft());
    this->DeleteNode(nodes[rid].cright());
    nodes[rid].set_leaf(value);
  }