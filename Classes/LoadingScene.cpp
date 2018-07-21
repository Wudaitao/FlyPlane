#include "LoadingScene.h"
#include "GameScene.h"
#include "Constants.h"
#include "Enemy.h"

Scene* LoadingScene::CreateScene() {
	return LoadingScene::create();
}

bool LoadingScene::init() {
	do {
		CC_BREAK_IF(!Scene::init());
		//ͨ�����ؾ���֡�ļ��������黺�浽���鼯�ļ���
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");
		auto bg = Sprite::createWithSpriteFrameName("background.png");
		bg->setPosition(VISIBLE_ORIGIN + VISIBLE_SIZE / 2);
		this->addChild(bg, -1, 1);

		auto title = Sprite::createWithSpriteFrameName("shoot_copyright.png");
		title->setPosition(VISIBLE_ORIGIN + VISIBLE_SIZE / 2+Vec2(0,100));
		this->addChild(title, 1, 2);

		auto loading = Sprite::create();
		loading->setPosition(VISIBLE_ORIGIN + VISIBLE_SIZE / 2 + Vec2(0, -200));
		this->addChild(loading);

		auto ani = Animation::create();
		for(auto i = 0; i < 4; i++) {
			auto png = StringUtils::format("game_loading%d.png", i+1);
			ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
		}
		ani->setDelayPerUnit(0.2f);
		ani->setLoops(4);
		auto seq = Sequence::create(Animate::create(ani), CallFunc::create([](){
			//������ת
			auto scene = GameScene::CreateScene();
			Director::getInstance()->replaceScene(TransitionProgressInOut::create(1,scene));
		}), nullptr);
			loading->runAction(seq);

		//�����ɻ����������뻺��
		
		//	a.������������
		auto aniHeroFly = Animation::create();
		//  b.��Ӷ���֡,�Ӿ���֡�����в��ҳ�����
		aniHeroFly->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2.png"));
		aniHeroFly->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
		//  c.���ö����л�ʱ��
		aniHeroFly->setDelayPerUnit(TIME_BREAK_1);
		aniHeroFly->setLoops(-1);
		AnimationCache::getInstance()->addAnimation(aniHeroFly, HERO_FLY_ANIMATION);

		//��л����ж���
		auto aniBigEnemyFly = Animation::create();
		aniBigEnemyFly->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
		aniBigEnemyFly->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
		aniBigEnemyFly->setDelayPerUnit(TIME_BREAK_1);
		aniBigEnemyFly->setLoops(-1);
		AnimationCache::getInstance()->addAnimation(aniBigEnemyFly, BIG_ENEMY_FLY_ANIMATION);
		
		//�����л����𶯻����뻺��
		//С�л�׹��
		auto aniSmallEnemyDown = Animation::create();
		for (int i = 0; i < 4; i++) {
			auto frameName = StringUtils::format("enemy1_down%d.png", i + 1);
			aniSmallEnemyDown->addSpriteFrame(CCSpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
		}
		aniSmallEnemyDown->setDelayPerUnit(TIME_BREAK_3);
		aniSmallEnemyDown->setLoops(1);
		AnimationCache::getInstance()->addAnimation(aniSmallEnemyDown, SMALL_ENEMY_DOWN_ANIMATION);
		//�ел�׹��
		auto aniMiddleEnemyDown = Animation::create();
		for (int i = 0; i < 4; i++) {
			auto frameName = StringUtils::format("enemy2_down%d.png", i + 1);
			aniMiddleEnemyDown->addSpriteFrame(CCSpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
		}
		aniMiddleEnemyDown->setDelayPerUnit(TIME_BREAK_3);
		aniMiddleEnemyDown->setLoops(1);
		AnimationCache::getInstance()->addAnimation(aniMiddleEnemyDown, MIDDLE_ENEMY_DOWN_ANIMATION);
		//��л�׹��
		auto aniBigEnemyDown = Animation::create();
		for (int i = 0; i < 6; i++) {
			auto frameName = StringUtils::format("enemy3_down%d.png", i + 1);
			aniBigEnemyDown->addSpriteFrame(CCSpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
		}
		aniBigEnemyDown->setDelayPerUnit(TIME_BREAK_3);
		aniBigEnemyDown->setLoops(1);
		AnimationCache::getInstance()->addAnimation(aniBigEnemyDown, BIG_ENEMY_DOWN_ANIMATION);
		//�ел�����
		auto aniMiddleEnemyHit = Animation::create();
		aniMiddleEnemyHit->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_hit.png"));
		aniMiddleEnemyHit->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2.png"));
		aniMiddleEnemyHit->setDelayPerUnit(TIME_BREAK_3);
		aniMiddleEnemyHit->setLoops(1);
		AnimationCache::getInstance()->addAnimation(aniMiddleEnemyHit, MIDDLE_ENEMY_HIT_ANIMATION);
		//��л�����
		auto aniBigEnemyHit = Animation::create();
		aniBigEnemyHit->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_hit.png"));
		aniBigEnemyHit->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
		aniBigEnemyHit->setDelayPerUnit(0.2f);
		aniBigEnemyHit->setLoops(1);
		AnimationCache::getInstance()->addAnimation(aniBigEnemyHit, BIG_ENEMY_HIT_ANIMATION);

		return true;
	} while (0);
	return false;
}

