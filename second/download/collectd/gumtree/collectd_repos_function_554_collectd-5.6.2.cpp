static void MPL3115_adjust_oversampling(void) {
  int new_val = 0;

  if (config_oversample > 100) {
    new_val = 128;
    mpl3115_oversample = MPL3115_CTRL_REG1_OST_128;
  } else if (config_oversample > 48) {
    new_val = 64;
    mpl3115_oversample = MPL3115_CTRL_REG1_OST_64;
  } else if (config_oversample > 24) {
    new_val = 32;
    mpl3115_oversample = MPL3115_CTRL_REG1_OST_32;
  } else if (config_oversample > 12) {
    new_val = 16;
    mpl3115_oversample = MPL3115_CTRL_REG1_OST_16;
  } else if (config_oversample > 6) {
    new_val = 8;
    mpl3115_oversample = MPL3115_CTRL_REG1_OST_8;
  } else if (config_oversample > 3) {
    new_val = 4;
    mpl3115_oversample = MPL3115_CTRL_REG1_OST_4;
  } else if (config_oversample > 1) {
    new_val = 2;
    mpl3115_oversample = MPL3115_CTRL_REG1_OST_2;
  } else {
    new_val = 1;
    mpl3115_oversample = MPL3115_CTRL_REG1_OST_1;
  }

  DEBUG("barometer: MPL3115_adjust_oversampling - correcting oversampling from "
        "%d to %d",
        config_oversample, new_val);
  config_oversample = new_val;
}