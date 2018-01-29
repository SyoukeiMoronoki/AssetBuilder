#pragma once
#include <HalEngine.h>

namespace Asset
{

namespace Texture
{
extern class Texture ENEMY_BOSS;
extern class Texture ENEMY_WEAK_POINT;
extern class Texture ENEMY_ZAKO1;
extern class Texture ENEMY_ZAKO2;
extern class Texture FIELD_BG;
extern class Texture FIELD_BG_SONAR;
extern class Texture FIELD_BOYA;
extern class Texture FIELD_GROUND;
extern class Texture FIELD_GROUND_NORMAL;
extern class Texture FIELD_SKY;
extern class Texture FIELD_ZENITH;
extern class Texture FONT_NUMBER;
extern class Texture PLAYER_BULLET;
extern class Texture PLAYER_BULLET_EFFECT;
extern class Texture PLAYER_SHADOW000;
extern class Texture PLAYER_TARGET;
extern class Texture TEXT_BONUS;
extern class Texture TEXT_HP;
extern class Texture TEXT_PRESS_ABUTTON;
extern class Texture TEXT_RESULT;
extern class Texture TEXT_SCORE;
extern class Texture TEXT_SONAR;
extern class Texture TEXT_TIME;
extern class Texture TEXT_TIME_UP;
extern class Texture TEXT_TITLE;
extern class Texture TEXT_TUTORIAL;
extern class Texture UI_EAR_GAUGE;
extern class Texture UI_HPGAUGE;
extern class Texture UI_KEYBOARD;
extern class Texture UI_PLAYER_ID;
extern class Texture UI_TEATER;
} // namespace Texture

namespace Shader
{
extern ShaderResource ENEMY_BODY;
extern ShaderResource ENEMY_SHADOW;
extern ShaderResource GROUND;
extern ShaderResource LIGHTING_GROUND;
extern ShaderResource PLAYER_BODY;
extern ShaderResource PLAYER_SHADOW;
extern ShaderResource SKY;
extern ShaderResource ZENITH;
} // namespace Shader

namespace Material
{
extern class Material ENEMY_BODY;
extern class Material ENEMY_SHADOW;
extern class Material GROUND;
extern class Material LIGHTING_GROUND;
extern class Material PLAYER_BODY;
extern class Material PLAYER_SHADOW;
extern class Material SKY;
extern class Material ZENITH;
} // namespace Material

namespace Spine
{
extern SpineResource ANUBIS;
extern SpineResource SKELETON;
extern SpineResource TEST;
} // namespace Spine

namespace Fbx
{
} // namespace Fbx

namespace Model
{
extern ModelData CART;
extern ModelData DOITYU;
extern ModelData SKYBOX;
} // namespace Model

} // namespace Asset
