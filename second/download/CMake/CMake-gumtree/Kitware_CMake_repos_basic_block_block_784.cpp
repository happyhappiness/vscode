(std::vector<cmXCodeObject*>::const_iterator i = this->List.begin();
         i != this->List.end(); ++i) {
      cmXCodeObject* o = *i;
      if (o->IsA == t) {
        return o;
      }
    }