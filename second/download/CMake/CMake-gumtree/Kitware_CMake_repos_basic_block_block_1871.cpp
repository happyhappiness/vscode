{
      std::cout << "Problem parsing /proc/meminfo" << std::endl;
      fclose(fd);
      return false;
    }