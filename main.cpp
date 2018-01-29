#include "AssetBuilder.h"

int main()
{
  AssetBuilder builder = AssetBuilder("AssetConfig.json");

  if (!builder.Load())
  {
    return 1;
  }

  printf(builder.ToString().c_str());

  std::string header = std::string();
  std::string cpp = std::string();

  builder.CreateProgram(&header, &cpp);

  printf("//=========================================\n");
  printf("// Asset.h\n");
  printf("//=========================================\n");
  printf(header.c_str());

  printf("//=========================================\n");
  printf("// Asset.cpp\n");
  printf("//=========================================\n");
  printf(cpp.c_str());

  printf("\n�I������ɂ͉����L�[�������Ă��������B");
  getchar();

  return 0;
}