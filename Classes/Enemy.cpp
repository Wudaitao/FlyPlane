#include "Enemy.h"

#include "Constants.h"



bool Enemy::initWithEnemyType(const EnemyType& type) {

	//���ﲻҪ���ó���createWithSpriteFrameName

	//�ó�Ա�����������ͣ���ס֮�����������ʱ����



	m_type = type;

	std::string frameName = "";



	switch (m_type)

	{

	case EnemyType::SMALL_ENEMY:

		frameName = "enemy1.png";

		this->m_speed = -SMALL_ENEMY_SPEED;

		this->m_hp = 1;

		this->m_score = 100;

		break;

	case EnemyType::MIDDLE_ENEMY:

		frameName = "enemy2.png";

		this->m_speed = -MIDDLE_ENEMY_SPEED;

		this->m_hp = 15;

		this->m_score = 800;

		break;

	case EnemyType::BIG_ENEMY:

		frameName = "enemy3_n1.png";

		this->m_speed = -BIG_ENEMY_SPEED;

		this->m_hp = 30;

		this->m_score = 1000;

		break;

	default:

		break;

	}

	if (!Sprite::initWithSpriteFrameName(frameName)) {

		return false;

	}



	//��л��ķ��ж���

	if (this->m_type == EnemyType::BIG_ENEMY) {



		auto ani = AnimationCache::getInstance()->getAnimation(BIG_ENEMY_FLY_ANIMATION);


		//2.��������װΪ����

		auto animator = Animate::create(ani);

		//3.�������ж���

		this->stopAllActions();//��ִ�з�ѭ������ֹͣ��������

		this->runAction(animator);



	}



	return true;

}



Enemy*  Enemy::create(const EnemyType& type) {

	auto enemy = new Enemy();

	if (enemy && enemy->initWithEnemyType(type)) {

		enemy->autorelease();//�����Զ�������

		return enemy;

	}

	delete enemy;

	enemy = nullptr;

	return nullptr;

}



void Enemy::down() {



	auto ani = AnimationCache::getInstance()->getAnimation(SMALL_ENEMY_DOWN_ANIMATION);
	switch (m_type)

	{

	
	case EnemyType::MIDDLE_ENEMY:
		ani = AnimationCache::getInstance()->getAnimation(MIDDLE_ENEMY_DOWN_ANIMATION);

		break;

	case EnemyType::BIG_ENEMY:

		ani = AnimationCache::getInstance()->getAnimation(BIG_ENEMY_DOWN_ANIMATION);

		break;

	default:

		break;

	}


	//2.��������װΪ����

	auto animator = Animate::create(ani);

	//������������

	/*auto seq = Sequence::create(animator, CallFuncN::create([this](Node *node) {

	this->removeChild(node);

	}), nullptr);

	*/

	auto seq = Sequence::create(animator, RemoveSelf::create(), NULL);

	this->runAction(seq);

	//3.�������ж���

	this->runAction(animator);





}



void Enemy::move() {

	this->setPositionY(this->getPositionY() + this->m_speed);

}

/*

���˺���Ĭ��һ�ε�һ��Ѫ

return �Ƿ��Ѫ������

*/

bool Enemy::hit() {

	//�Ѿ�����ֱ���˳�

	if (this->m_hp <= 0) {

		return true;

	}

	this->m_hp--;

	//���ڼ�Ѫ�Ƿ�������

	if (this->m_hp <= 0) {

		this->down();

		return true;

	}

	//���˶���

	else {

		switch (m_type)

		{

		case EnemyType::MIDDLE_ENEMY:

		{

			auto ani = AnimationCache::getInstance()->getAnimation(MIDDLE_ENEMY_HIT_ANIMATION);

			runAction(Animate::create(ani));

			break;

		}



		case EnemyType::BIG_ENEMY:

		{

			auto ani = AnimationCache::getInstance()->getAnimation(BIG_ENEMY_HIT_ANIMATION);

			runAction(Animate::create(ani));

			break;

		}

		break;

		default:

			break;

		}

	}

	return false;

}