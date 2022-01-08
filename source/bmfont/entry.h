#pragma once
#include <string>

namespace bmfont
{
  void Init();
  int Run(std::string configFile, std::string outputFile);
  void Destroy();
} // namespace bmfont
