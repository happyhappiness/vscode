{
        if ((low % 7) == 0) printf("\n        ");
        printf("{%u,%u,%d}", state.lencode[low].op, state.lencode[low].bits,
               state.lencode[low].val);
        if (++low == size) break;
        putchar(',');
    }