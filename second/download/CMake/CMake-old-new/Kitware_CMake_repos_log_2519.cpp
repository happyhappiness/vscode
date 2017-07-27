fprintf(fout, "set(CMAKE_%s_FLAGS \"${CMAKE_%s_FLAGS}"
                    " ${COMPILE_DEFINITIONS}\")\n",
              li->c_str(), li->c_str())