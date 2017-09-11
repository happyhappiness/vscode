   * \param new leaf value
   */
  inline void ChangeToLeaf(int rid, float value) {
    CHECK(nodes[nodes[rid].cleft() ].is_leaf());
    CHECK(nodes[nodes[rid].cright()].is_leaf());
    this->DeleteNode(nodes[rid].cleft());
    this->DeleteNode(nodes[rid].cright());
    nodes[rid].set_leaf(value);
