{
      CPpmd7_Node *node = NODE(next);
      node->Next = n;
      n = NODE(n)->Prev = next;
      next = *(const CPpmd7_Node_Ref *)node;
      node->Stamp = 0;
      node->NU = (UInt16)nu;
    }