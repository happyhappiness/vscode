
    char buffer[m_canvas->width() + 1];

    Canvas::attributes_list attributes;
    attributes.push_back(Attributes(buffer, Attributes::a_normal, Attributes::color_default));

    char* last = (*itr)->print(buffer, buffer + m_canvas->width(), &attributes, m_object);

    m_canvas->print_attributes(0, position, buffer, last, &attributes);
  }
}

}
