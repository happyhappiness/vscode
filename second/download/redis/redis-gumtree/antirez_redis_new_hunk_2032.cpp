                }
            }
            if (i != HLL_REGISTERS) {
                addReplySds(c,sdsnew(invalid_hll_err));
                return;
            }
        }
