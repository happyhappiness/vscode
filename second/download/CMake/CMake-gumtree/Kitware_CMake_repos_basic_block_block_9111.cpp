{
    CPpmd_Void_Ref successor;
    CPpmd_State *s;
    c = SUFFIX(c);
    if (c->NumStats != 1)
    {
      for (s = STATS(c); s->Symbol != p->FoundState->Symbol; s++);
    }
    else
      s = ONE_STATE(c);
    successor = SUCCESSOR(s);
    if (successor != upBranch)
    {
      c = CTX(successor);
      if (numPs == 0)
        return c;
      break;
    }
    ps[numPs++] = s;
  }