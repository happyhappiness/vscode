(k = 0; k < 8; k++)
    {
      UInt16 *dest = p->BinSumm[i] + k;
      UInt16 val = (UInt16)(PPMD_BIN_SCALE - kInitBinEsc[k] / (i + 2));
      for (m = 0; m < 64; m += 8)
        dest[m] = val;
    }