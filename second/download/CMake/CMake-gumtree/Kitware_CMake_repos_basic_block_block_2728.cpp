{
  cairo_t* cr;
  char* filename;
  cairo_status_t status;
  cairo_surface_t* surface;
  if (argc != 2) {
    g_printerr("Usage: cairosimple OUTPUT_FILENAME\n");
    return 1;
  }
  filename = argv[1];
  surface =
    cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 2 * RADIUS, 2 * RADIUS);
  cr = cairo_create(surface);
  cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
  cairo_paint(cr);
  draw_text(cr);
  cairo_destroy(cr);
  status = cairo_surface_write_to_png(surface, filename);
  cairo_surface_destroy(surface);
  if (status != CAIRO_STATUS_SUCCESS) {
    g_printerr("Could not save png to '%s'\n", filename);
    return 1;
  }
  return 0;
}