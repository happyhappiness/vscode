{
      ParseString();
      std::string name = this->String;
      ExpectOrDie(':', "between name and value");
      ParseString();
      std::string value = this->String;
      this->Command[name] = value;
    }