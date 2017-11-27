void module_register(void){
    plugin_register_complex_config("tail_csv", tcsv_config);
    plugin_register_init("tail_csv", tcsv_init);
    plugin_register_shutdown("tail_csv", tcsv_shutdown);
}