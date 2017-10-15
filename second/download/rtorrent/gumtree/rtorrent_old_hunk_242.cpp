                         int flags = TextElementStringBase::flag_normal,
                         int attributes = Attributes::a_invalid,
                         TextElement::extent_type length = TextElement::extent_full) {
  return new TextElementStringSlot<slot_type>(slot, flags, attributes, length);
}

}

#endif
