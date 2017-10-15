
  TextElement*        m_branch1;
  TextElement*        m_branch2;
};

template <typename slot_type>
inline TextElementBranchVoid<slot_type>*
text_element_branch_void(const slot_type& slot, TextElement* branch1, TextElement* branch2) {
  return new TextElementBranchVoid<slot_type>(slot, branch1, branch2);
}

template <typename slot_type>
inline TextElementBranch<slot_type>*
text_element_branch(const slot_type& slot, TextElement* branch1, TextElement* branch2) {
  return new TextElementBranch<slot_type>(slot, branch1, branch2);
}

}

#endif
