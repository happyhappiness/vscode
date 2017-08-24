{
    /* libnssckbi.so not needed but already loaded --> unload it! */
    infof(data, "unloading %s\n", trust_library);
    nss_unload_module(&trust_module);
  }