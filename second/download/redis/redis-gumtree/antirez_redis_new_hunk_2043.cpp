                }
            }
            if (i != HLL_REGISTERS) {
                addReplyError(c,invalid_hll_err);
                return;
            }
        }
