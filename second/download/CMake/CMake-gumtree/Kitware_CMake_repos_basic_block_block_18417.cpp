{
    smallest = child;
    if (child->left != NULL && less_than(child->left, smallest))
      smallest = child->left;
    if (child->right != NULL && less_than(child->right, smallest))
      smallest = child->right;
    if (smallest == child)
      break;
    heap_node_swap(heap, child, smallest);
  }