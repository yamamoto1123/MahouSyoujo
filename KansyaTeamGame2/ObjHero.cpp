//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjHero::Init()
{
	m_px = 0;
	m_py = 0;
	m_vx = 0;
	m_vy = 0;
	m_posture = 0;
	m_anime = 0;
	m_anitime = 0;
	atk_anime = 0;
	atk_anitime = 0;

	//あたり判定用Hitboxを作成
	Hits::SetHitBox(this, m_px, m_py, 50, 50, ELEMENT_PLAYER, OBJ_HERO, 1);
	
}

//アクション
void CObjHero::Action()
{


	//キーを押すと移動
	if (Input::GetVKey(VK_LEFT) == true)
	{
		m_vx -= 0.1;
		m_posture = 0;

		m_anitime += 1;

	}
	else if (Input::GetVKey(VK_RIGHT) == true)
	{
		m_vx += 0.1;
		m_posture = 1;

		m_anitime += 1;


	}
	//どちらも押していない場合は減速させる。
	else
	{

		m_anime = 0;
		if (m_vx > 0)//左方向に動いているとき
		{
			m_vx -= 0.2;

			if (m_vx <= 0)
				m_vx = 0;


		}
		if (m_vx < 0)//右方向に動いているとき
		{
			m_vx += 0.2;
			if (m_vx >= 0)
				m_vx = 0;

		}
	}
	if (m_anitime >= 10)
	{
		m_anime++;

		m_anitime = 0;
	}

	if (m_anime > 1)
		m_anime = 0;
	//最高速度決定
	if (m_vx >= 6)
		m_vx = 6;
	if (m_vx <= -6)
		m_vx = -6;
	m_px += m_vx;

	//キーを押すと移動
	if (Input::GetVKey('X') == true)
	{
		atk_anime = 1;
	}
	else
		atk_anime = 0;

	//test用　画面外に行かないように
	if (m_px > 750)
	{
		m_px = 750;
		m_vx = 0;
	}
	else if (m_px < 0)
	{
		m_px = 0;
		m_vx = 0;
	}

	//HitBoxの内容を更新
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);
}
//ドロー
void CObjHero::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top =(atk_anime*50)+0.0f;
	src.m_left =(m_anime*50)+0.0f;
	src.m_right =(m_anime*50)+50.0f;
	src.m_bottom = (atk_anime * 50) + 50.0f;
	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left =(50.0f*m_posture)+m_px;
	dst.m_right = (50.0f - 50*m_posture )+ m_px;
	dst.m_bottom = 50.0f;

	//描画
	Draw::Draw(0, &src, &dst, c, 0.0f);
}