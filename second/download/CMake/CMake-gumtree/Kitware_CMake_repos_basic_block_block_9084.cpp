{
    CPpmd7_Node *node = NODE(n);
    UInt32 nu = (UInt32)node->NU;
    for (;;)
    {
      CPpmd7_Node *node2 = NODE(n) + nu;
      nu += node2->NU;
      if (node2->Stamp != 0 || nu >= 0x10000)
        break;
      NODE(node2->Prev)->Next = node2->Next;
      NODE(node2->Next)->Prev = node2->Prev;
      node->NU = (UInt16)nu;
    }
    n = node->Next;
  }