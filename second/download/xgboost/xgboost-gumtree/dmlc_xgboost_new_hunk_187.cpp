      } while (b != b_end);
    }
    this->size = dst - data;
    const RType tol = 10;
    RType err_mingap, err_maxgap, err_wgap;
    this->FixError(&err_mingap, &err_maxgap, &err_wgap);
    if (err_mingap > tol || err_maxgap > tol || err_wgap > tol) {
      utils::Printf("INFO: mingap=%g, maxgap=%g, wgap=%g\n",
                    err_mingap, err_maxgap, err_wgap);
    }

    utils::Assert(size <= sa.size + sb.size, "bug in combine");
  }
  // helper function to print the current content of sketch
