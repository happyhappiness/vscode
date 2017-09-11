utils::Assert(fi.Read(&(*p_str)[0], sizeof(char) * sz) != 0,
                    "Read pickle string");