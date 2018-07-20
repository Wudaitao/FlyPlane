#pragma once
#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;
//��Ϸ����
class GameScene : public Scene {
public:
	GameScene() :m_offset(Vec2::ZERO), m_totalScore(0) ,m_doubleBulletCount(0),m_ufoType(0), m_totalBombCount(2), IsPause(0){}//��ʼ���б�

	static Scene* CreateScene();
		
	bool init() override;
	
	CREATE_FUNC(GameScene);

	void update(float) override;

private:
	Vec2 m_offset;				//��¼��������ɻ����ĵ�ƫ������

	Vector<Sprite *> m_bullets; //�����Ч���ӵ�

	Vector<Sprite *> m_UFO;     //��ŵ���

	Vector<Enemy *> m_enemys;   //�����Ч�ĵл�

	int m_totalScore;           //�ܵķ���

	int m_totalBombCount;         //�ܵ�ը����

	int m_doubleBulletCount;    //ʣ��˫�ӵ���Ŀ

	int m_ufoType;              //��������

	void createBullet(float);

	int IsPause;				//�Ƿ���ͣ��

	//void createTwoBullet(float);

	void createEnemy(const EnemyType&);

	void createSmallEnemy(float);

	void createMiddleEnemy(float);

	void createBigEnemy(float);

	void createUFO(float);

	void updateBomb();

/*public:
	Sprite * bg1;
	Sprite * bg2;
	void initbg();
*/
};


