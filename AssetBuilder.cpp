#include "AssetBuilder.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>
#include <set>
#include <direct.h>

AssetBuilder::AssetBuilder(const char* path)
  : config_path_(path)
  , engine_name_()
  , asset_name_()
  , source_path_()
  , asset_datas_()
{}

AssetBuilder::~AssetBuilder()
{
  for (AssetData* data : this->asset_datas_)
  {
    delete data;
  }
}

bool AssetBuilder::Load()
{
  std::ifstream ifs(this->config_path_);
  if (ifs.fail())
  {
    std::cerr << "ファイルを開けませんでした" << std::endl;
    return false;
  }
  int begin = static_cast<int>(ifs.tellg());
  ifs.seekg(0, ifs.end);
  int end = static_cast<int>(ifs.tellg());
  int size = end - begin;
  ifs.clear();
  ifs.seekg(0, ifs.beg);
  char *str = new char[size + 1];
  str[size] = '\0';
  ifs.read(str, size);

  JsonParser* json = new JsonParser();
  JsonNode* root = json->Parse(str);
  this->engine_name_ = root->GetString("EngineName")->StringValue();
  this->asset_name_ = root->GetString("AssetName")->StringValue();
  this->target_path_  = root->GetString("TargetPath")->StringValue();
  this->source_path_ = root->GetString("SourcePath")->StringValue();

  JsonList* asset_types = root->GetList("AssetTypes");
  int asset_type_count = asset_types->GetSize();
  for (int i = 0; i < asset_type_count; ++i)
  {
    AssetData* data = new AssetData(asset_types->GetNode(i));
    data->Load(this->asset_name_, this->target_path_);
    this->asset_datas_.push_back(data);
  }
  return true;
}

void AssetBuilder::CreateProgram(std::string* header, std::string* cpp)
{
  //Header head
  header->append("#pragma once\n");
  header->append("#include <" + this->engine_name_ + ".h>\n");
  std::set<std::string> includes = std::set<std::string>();
  for (AssetData* data : this->asset_datas_)
  {
    data->GetAssetType().GetIncludePaths(&includes);
  }
  for (const std::string& include : includes)
  {
    header->append("#include \"" + include + "\"\n");
  }
  header->append("\n");
  header->append("namespace Asset\n");
  header->append("{\n");
  header->append("\n");

  //cpp head
  cpp->append("#include \"Asset.h\"\n");
  cpp->append("\n");
  cpp->append("namespace Asset\n");
  cpp->append("{\n");
  cpp->append("\n");

  //Body
  for (AssetData* data : this->asset_datas_)
  {
    data->CreateProgram(header, cpp);
  }

  //Header bottom
  header->append("} // namespace Asset\n");

  //cpp bottom
  cpp->append("} // namespace Asset\n");

  _mkdir(this->source_path_.c_str());

  //write headder program
  const std::string header_path = this->source_path_ + "/" + "Asset.h";
  std::ofstream output_header(header_path);
  if (output_header)
  {
    output_header << *header;
    output_header.close();
  }

  //write headder program
  const std::string cpp_path = this->source_path_ + "/" + "Asset.cpp";
  std::ofstream output_cpp(cpp_path);
  if (output_cpp)
  {
    output_cpp << *cpp;
    output_cpp.close();
  }
}

const std::string AssetBuilder::ToString()
{
  std::string ret = std::string();

  ret.append("AssetName = ");
  ret.append(this->asset_name_);
  ret.append("\n");

  ret.append("TargetPath = ");
  ret.append(this->target_path_);
  ret.append("\n");

  ret.append("SourcePath = ");
  ret.append(this->source_path_);
  ret.append("\n");

  for (AssetData* data : this->asset_datas_)
  {
    ret.append(data->ToString());
  }

  return ret;
}
