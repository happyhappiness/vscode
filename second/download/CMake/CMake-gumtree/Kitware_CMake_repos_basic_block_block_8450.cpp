{
      const std::string& name = *it;
      if (it != members.begin())
        document_ += ',';
      document_ += valueToQuotedString(name.c_str());
      document_ += yamlCompatiblityEnabled_ ? ": " : ":";
      writeValue(value[name]);
    }