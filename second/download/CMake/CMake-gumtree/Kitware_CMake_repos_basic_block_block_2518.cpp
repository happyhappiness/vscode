{
    {
      kwsys::ofstream out("bom.txt", kwsys::ofstream::binary);
      out.write(reinterpret_cast<const char*>(expected_bom_data[i] + 1),
                *expected_bom_data[i]);
      out.write(reinterpret_cast<const char*>(file_data[i] + 1),
                file_data[i][0]);
    }

    kwsys::ifstream in("bom.txt", kwsys::ofstream::binary);
    kwsys::FStream::BOM bom = kwsys::FStream::ReadBOM(in);
    if (bom != expected_bom[i]) {
      std::cout << "Unexpected BOM " << i << std::endl;
      return 1;
    }
    char data[max_test_file_size];
    in.read(data, file_data[i][0]);
    if (!in.good()) {
      std::cout << "Unable to read data " << i << std::endl;
      return 1;
    }

    if (memcmp(data, file_data[i] + 1, file_data[i][0]) != 0) {
      std::cout << "Incorrect read data " << i << std::endl;
      return 1;
    }
  }