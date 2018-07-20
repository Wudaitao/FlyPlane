#pragma once

#include "cocos2d.h"

USING_NS_CC;

//ö���࣬��ȫ����
enum class EnemyType {
	SMALL_ENEMY,
	MIDDLE_ENEMY,
	BIG_ENEMY
};

class Enemy :public Sprite {
public:
	Enemy() :m_type(EnemyType::SMALL_ENEMY), m_speed(0), m_hp(0), m_score(0) {}
	bool initWithEnemyType(const EnemyType& type) ;
	static Enemy* create(const EnemyType& type);
	void move();
	bool hit();
	void down();
	//�ƶ��ٶ�
	CC_SYNTHESIZE(float,m_speed,Speed);
	//����ֵ
	CC_SYNTHESIZE_READONLY(int, m_hp, HP);
	//������ֵ
	CC_SYNTHESIZE_READONLY(int, m_score, Score);
private:
	EnemyType m_type;
	//float m_speed;
};