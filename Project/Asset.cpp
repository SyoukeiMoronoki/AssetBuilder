#include "Asset.h"

namespace Asset
{

namespace Texture
{
class Texture ENEMY_BOSS("Asset/Texture/enemy/boss.png");
class Texture ENEMY_WEAK_POINT("Asset/Texture/enemy/weak_point.png");
class Texture ENEMY_ZAKO1("Asset/Texture/enemy/zako1.png");
class Texture ENEMY_ZAKO2("Asset/Texture/enemy/zako2.png");
class Texture FIELD_BG("Asset/Texture/field/bg.png");
class Texture FIELD_BG_SONAR("Asset/Texture/field/bg_sonar.png");
class Texture FIELD_BOYA("Asset/Texture/field/boya.png");
class Texture FIELD_GROUND("Asset/Texture/field/ground.png");
class Texture FIELD_GROUND_NORMAL("Asset/Texture/field/ground_normal.png");
class Texture FIELD_SKY("Asset/Texture/field/sky.png");
class Texture FIELD_ZENITH("Asset/Texture/field/zenith.png");
class Texture FONT_NUMBER("Asset/Texture/font/number.png");
class Texture PLAYER_BULLET("Asset/Texture/player/bullet.png");
class Texture PLAYER_BULLET_EFFECT("Asset/Texture/player/bullet_effect.png");
class Texture PLAYER_SHADOW000("Asset/Texture/player/shadow000.jpg");
class Texture PLAYER_TARGET("Asset/Texture/player/target.png");
class Texture TEXT_BONUS("Asset/Texture/text/BONUS.png");
class Texture TEXT_HP("Asset/Texture/text/HP.png");
class Texture TEXT_PRESS_ABUTTON("Asset/Texture/text/PressAButton.png");
class Texture TEXT_RESULT("Asset/Texture/text/RESULT.png");
class Texture TEXT_SCORE("Asset/Texture/text/SCORE.png");
class Texture TEXT_SONAR("Asset/Texture/text/SONAR.png");
class Texture TEXT_TIME("Asset/Texture/text/TIME.png");
class Texture TEXT_TIME_UP("Asset/Texture/text/TimeUP.png");
class Texture TEXT_TITLE("Asset/Texture/text/TITLE.png");
class Texture TEXT_TUTORIAL("Asset/Texture/text/Tutorial.png");
class Texture UI_EAR_GAUGE("Asset/Texture/ui/EarGauge.png");
class Texture UI_HPGAUGE("Asset/Texture/ui/HPGauge.png");
class Texture UI_KEYBOARD("Asset/Texture/ui/keyboard.png");
class Texture UI_PLAYER_ID("Asset/Texture/ui/player_id.png");
class Texture UI_TEATER("Asset/Texture/ui/teater.png");
} // namespace Texture

namespace Shader
{
ShaderResource ENEMY_BODY("Asset/Shader/EnemyBody.cso");
ShaderResource ENEMY_SHADOW("Asset/Shader/EnemyShadow.cso");
ShaderResource GROUND("Asset/Shader/Ground.cso");
ShaderResource LIGHTING_GROUND("Asset/Shader/LightingGround.cso");
ShaderResource PLAYER_BODY("Asset/Shader/PlayerBody.cso");
ShaderResource PLAYER_SHADOW("Asset/Shader/PlayerShadow.cso");
ShaderResource SKY("Asset/Shader/Sky.cso");
ShaderResource ZENITH("Asset/Shader/Zenith.cso");
} // namespace Shader

namespace Material
{
class Material ENEMY_BODY(Shader::ENEMY_BODY);
class Material ENEMY_SHADOW(Shader::ENEMY_SHADOW);
class Material GROUND(Shader::GROUND);
class Material LIGHTING_GROUND(Shader::LIGHTING_GROUND);
class Material PLAYER_BODY(Shader::PLAYER_BODY);
class Material PLAYER_SHADOW(Shader::PLAYER_SHADOW);
class Material SKY(Shader::SKY);
class Material ZENITH(Shader::ZENITH);
} // namespace Material

namespace Spine
{
SpineResource ANUBIS("Asset/Spine/Anubis.png");
SpineResource SKELETON("Asset/Spine/skeleton.png");
SpineResource TEST("Asset/Spine/test.atlas");
} // namespace Spine

namespace Fbx
{
} // namespace Fbx

namespace Model
{
ModelData CART("Asset/Model/cart/horse.bmp");
ModelData DOITYU("Asset/Model/doityu/doityu_plane_lst.png");
ModelData SKYBOX("Asset/Model/skybox/skybox.x");
} // namespace Model

} // namespace Asset
