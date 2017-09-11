utils::Assert(fi.Read(&(*out_data)[0], out_data->size() * sizeof(SparseBatch::Entry)) != 0, 
                    "invalid input file format");