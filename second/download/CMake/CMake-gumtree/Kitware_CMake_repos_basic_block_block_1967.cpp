(osvi.wSuiteMask & VER_SUITE_DATACENTER) {
            this->OSRelease += " DataCenter Server";
          } else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE) {
            this->OSRelease += " Advanced Server";
          } else {
            this->OSRelease += " Server";
          }