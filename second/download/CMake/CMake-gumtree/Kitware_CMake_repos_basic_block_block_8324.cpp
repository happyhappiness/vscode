{
    isDouble = isDouble || in(*inspect, '.', 'e', 'E', '+') ||
               (*inspect == '-' && inspect != token.start_);
  }