{
      int k = (int)(MASK(s->Symbol));
      hiCnt += (s->Freq & k);
      ps[i] = s++;
      i -= k;
    }