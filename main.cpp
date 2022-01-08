#include "bmfont/entry.h"

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    fprintf(stderr, "invalid number of arguments\n");
    fprintf(stderr, "example: bmfont.exe config output\n");
    return EXIT_FAILURE;
  }

  bmfont::Init();
  int ret = bmfont::Run(argv[1], argv[2]);
  bmfont::Destroy();

  return ret;
}
