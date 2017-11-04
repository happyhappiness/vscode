fprintf(out, "%s0x%08lxUL%s", n % 5 ? "" : "    ", table[n],
                n == 255 ? "\n" : (n % 5 == 4 ? ",\n" : ", "));