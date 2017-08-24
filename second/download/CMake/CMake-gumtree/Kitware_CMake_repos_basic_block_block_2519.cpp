{
      kwsys::ofstream out("bom.txt", kwsys::ofstream::binary);
      out.write(reinterpret_cast<const char*>(expected_bom_data[i] + 1),
                *expected_bom_data[i]);
      out.write(reinterpret_cast<const char*>(file_data[i] + 1),
                file_data[i][0]);
    }