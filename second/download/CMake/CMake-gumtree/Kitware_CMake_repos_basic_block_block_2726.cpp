{
    int width, height;
    double angle = (360. * i) / N_WORDS;
    double red;
    cairo_save(cr);
    /* Gradient from red at angle == 60 to blue at angle == 240 */
    red = (1 + cos((angle - 60) * G_PI / 180.)) / 2;
    cairo_set_source_rgb(cr, red, 0, 1.0 - red);
    cairo_rotate(cr, angle * G_PI / 180.);
    /* Inform Pango to re-layout the text with the new transformation */
    pango_cairo_update_layout(cr, layout);
    pango_layout_get_size(layout, &width, &height);
    cairo_move_to(cr, -((double)width / PANGO_SCALE) / 2, -RADIUS);
    pango_cairo_show_layout(cr, layout);
    cairo_restore(cr);
  }