void
TextElement::push_attribute(Canvas::attributes_list* attributes, Attributes value) {
  Attributes base = attributes->back();
  
  if (value.colors() == Attributes::color_invalid)
    value.set_colors(base.colors());

  if (value.attributes() == Attributes::a_invalid)
    value.set_attributes(base.attributes());

  if (base.position() == value.position())
    attributes->back() = value;
  else if (base.colors() != value.colors() || base.attributes() != value.attributes())
    attributes->push_back(value);
}