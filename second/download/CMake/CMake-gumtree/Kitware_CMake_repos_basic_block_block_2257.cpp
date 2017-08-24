{
    std::vector<std::string> base_components;
    // Use the given base path.
    SystemTools::SplitPath(in_base, base_components);

    // Append base path components to the output path.
    out_components.push_back(base_components[0]);
    SystemToolsAppendComponents(out_components, base_components.begin() + 1,
                                base_components.end());
  }