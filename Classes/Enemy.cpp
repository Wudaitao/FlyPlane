#include "Enemy.h"
#include "Constants.h"

bool Enemy::initWithEnemyType(const EnemyType& type) {
	//这里不要调用成了createWithSpriteFrameName
	//用成员变量保存类型，记住之后后续可以随时访问

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
	if (!Sprite::initWithSpriteFrameName(frameName)){
		return false;
	}

	//大敌机的飞行动画
	if (this->m_type == EnemyType::BIG_ENEMY) {

		auto ani = Animation::create();
		ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
		ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
		//  c.设置动画切换时长
		ani->setDelayPerUnit(TIME_BREAK_1);
		//  d.设置迭代次数
		ani->setLoops(-1);
		//2.将动画封装为动作
		auto animator = Animate::create(ani);
		//3.精灵运行动作
		this->stopAllActions();//在执行非循环，先停止其他动作
		this->runAction(animator);

	}

	return true;
}

Enemy*  Enemy::create(const EnemyType& type) {
	auto enemy = new Enemy();
	if (enemy && enemy->initWithEnemyType( type)) {
		enemy->autorelease();//放入自动计数器
		return enemy;
	}
	delete enemy;
	enemy = nullptr;
	return nullptr;
}

void Enemy::down() {

	auto ani = Animation::create();

	switch (m_type)
	{
	case EnemyType::SMALL_ENEMY:
		for (int i = 0; i < 4; i++) {
			auto frameName = StringUtils::format("enemy1_down%d.png", i + 1);
			ani->addSpriteFrame(CCSpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
		}
		
		break;
	case EnemyType::MIDDLE_ENEMY:
		for (int i = 0; i < 4; i++) {
			auto frameName = StringUtils::format("enemy2_down%d.png", i + 1);
			ani->addSpriteFrame(CCSpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
		}
		break;
	case EnemyType::BIG_ENEMY:
		for (int i = 0; i < 6; i++) {
			auto frameName = StringUtils::format("enemy3_down%d.png", i + 1);
			ani->addSpriteFrame(CCSpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
		}
		break;
	default:
		break;
	}
	
	//  c.设置动画切换时长
	ani->setDelayPerUnit(TIME_BREAK_3);
	//  d.设置迭代次数
	ani->setLoops(1);
	//2.将动画封装为动作
	auto animator = Animate::create(ani);
	//动作函数序列
	/*auto seq = Sequence::create(animator, CallFuncN::create([this](Node *node) {
	this->removeChild(node);
	}), nullptr);
	*/
	auto seq = Sequence::create(animator, RemoveSelf::create(), NULL);
	this->runAction(seq);
	//3.精灵运行动作
	this->runAction(animator);
	
	
}

void Enemy::move() {
	this->setPositionY(this->getPositionY() + this->m_speed);
}
/*
	受伤函数默认一次掉一点血
	return 是否减血后死亡
*/
bool Enemy::hit() {
	//已经死亡直接退出
	if (this->m_hp <= 0) {
		return true;
	}
	this->m_hp--;
	//现在减血是否死亡·
	if (this->m_hp <= 0) {
		this->down();
		return true;
	}
	//受伤动画
	else {
		switch (m_type)
		{
		case EnemyType::MIDDLE_ENEMY:
		{
			auto ani = Animation::create();
			ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_hit.png"));
			ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2.png"));
			ani->setDelayPerUnit(0.2f);
			runAction(Animate::create(ani));
			break;
		}

		case EnemyType::BIG_ENEMY:
		{
			auto ani = Animation::create();
			ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_hit.png"));
			ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
			ani->setDelayPerUnit(0.2f);
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