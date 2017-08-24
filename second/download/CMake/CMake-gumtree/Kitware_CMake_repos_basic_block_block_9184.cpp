{
        RangeEnc_Encode(rc, sum, s->Freq, p->MinContext->SummFreq);
        p->FoundState = s;
        Ppmd7_Update1(p);
        return;
      }