#include "GameScene.h"
#include "Constants.h"
#include "time.h"
#include "SimpleAudioEngine.h"

auto cnt = 0;

Scene* GameScene::CreateScene() {
	return GameScene :: create();
}

bool GameScene::init() {
	//1.�ȵ��ø����init()
	if (!Scene::init()) {
		return false;
	}
	
	srand((unsigned int)time(NULL));
	//auto size = Director::getInstance()->getVisibleSize();
	//auto origin = Director::getInstance()->getVisibleOrigin();
	//ͨ�����ؾ��鼯�ļ��������鶼���浽���鼯������
	//auto bg = Sprite::create("shoot_background.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");
	auto bg = Sprite::createWithSpriteFrameName("background.png");

	//��������ļ�
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("game_music.mp3", true);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");
	//��ӷɻ�
	auto plane = Sprite::createWithSpriteFrameName("hero1.png");
	plane->setPosition(VISIBLE_ORIGIN + VISIBLE_SIZE / 2);
	this->addChild(plane, FOREROUND_ZORDER, PLANE_TAG);
	

	

	//���ɻ�ȥ��������
	//1.��������
	//	a.������������
	auto ani = Animation::create();
	
	//  b.��Ӷ���֡,�Ӿ���֡�����в��ҳ�����
	ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2.png"));
	ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
	//  c.���ö����л�ʱ��
	ani->setDelayPerUnit(TIME_BREAK_1);
	//  d.���õ�������
	ani->setLoops(-1);
	//2.��������װΪ����
	auto animator = Animate::create(ani);
	//3.�������ж���
	plane->runAction(animator);

	//��Ӵ����¼��Ĵ���
	//1.������������
	auto listener = EventListenerTouchOneByOne::create();
	//2.�ֽ��¼��������߼�
	//a.������ʼʱ
	//lambda���ʽ��[]���ֿ��ƶ��ⲿ�����ķ��ʣ�����һ�����Ĵ���
	//Ҳ����д[=]�Ⱥţ���ʾ�ⲿ���б�������ֵ���ݣ�Ҳ���Է��ʣ��������޸�
	//[&] ��ַ���������޸��ⲿ����
	listener->onTouchBegan = [=](Touch* t, Event* e) {
		Vec2 touchPos = t->getLocation();	
		this->m_offset = plane->getPosition() - touchPos;
		//�жϴ������Ƿ���planeͼƬ�ľ��α߿��ڣ�BoundingBox()���Ǿ��α߿�
		bool isContains = plane->getBoundingBox().containsPoint(touchPos);
		return isContains;
	};
	//b.�����������ƶ�
	listener->onTouchMoved = [=](Touch* t, Event* e){
		//log("moveing");		
		Vec2 touchPos = t->getLocation();
		if (this->IsPause == 0) {
			plane->setPosition(touchPos + this->m_offset);
			Vec2 deltaPos = t->getDelta();//�ϴδ������뵱ǰ�������������
			auto minX = plane->getContentSize().width / 2;
			auto minY = plane->getContentSize().height / 2;
			auto maxX = VISIBLE_SIZE.width - minX;
			auto maxY = VISIBLE_SIZE.height / 1.5 + minY;
			auto x = MAX(minX, MIN(maxX, plane->getPositionX()));
			auto y = MIN(maxY, plane->getPositionY());
			y = MAX(minY, y);
			plane->setPosition(x, y);
		}			
	};
	//c.��������
	listener->onTouchEnded = [](Touch* t, Event* e) {
		//log("ending");
	};
	//3.ע������¼����ַ���
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,plane);
	//getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, plane);
	//bg->setPosition(origin.x + size.width / 2, origin.y + size.height / 2);
	//bg->setPosition(origin+size / 2);
	//���ö�λ�����������½�
	//���� ��λ ���
	bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	//���������
	bg->getTexture()->setAliasTexParameters();
	//bg->setPositionX(origin.x + size.width / 2);
	//bg->setPositionY(origin.y + bg->getContentSize().height / 2);
	this->addChild(bg,BACKGROUND_ZORDER,BACKGROUND_TAG_1);

	auto bg2 = Sprite::createWithSpriteFrameName("background.png");
	bg2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	bg2->setPositionY(bg->getContentSize().height);
	bg2->getTexture()->setAliasTexParameters();
	this->addChild(bg2, BACKGROUND_ZORDER, BACKGROUND_TAG_2);

	/*auto ufo = Sprite::createWithSpriteFrameName("ufo1.png");
	auto minX = ufo->getContentSize().with / 2;
	auto maxX = VISIBLE_SIZE.width - ufo->getContentSize().width / 2;
	ufo->setPosition(rand()(int)(maxX - minX + 1) + minX, VISIBLE_SIZE.height + ufo->getContentSize().height / 2);
	this->addChild(ufo, FOREROUND_ZORDER, UFO_TAG);
	auto move1 = MoveBy::create(1, Vec2(0, -300));
	auto move2 = MOveTo::create(1.5f, Vec2(ufo->getPositionX(), ufo->getContentSize().height));
	ufo->runAction(Sequence(move1, move1->reverse(), move2), nullptr);
	*/

	////UI
	//�Ʒֱ�ǩ
	auto lblScore = Label::createWithBMFont("font.fnt", StringUtils::format("%d", this->m_totalScore));
	lblScore->setPosition(20, VISIBLE_SIZE.height - lblScore->getContentSize().height-10);
	this->addChild(lblScore, UI_ZORDER, LBL_SCORE_TAG);
	lblScore->setColor(Color3B(200, 2, 100));
	//lblScore->setAlignment(TextHAlignment::LEFT);
	lblScore->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

	//ը���˵�,�˵��кܶ๦��1
	auto normalBomb = Sprite::createWithSpriteFrameName("bomb.png");
	auto itemBomb = MenuItemSprite::create(normalBomb, normalBomb,[this] (Ref *) {
	
		if (this->IsPause==0) {
			for (auto enemy : this->m_enemys) {
				enemy->down();
				m_totalScore += enemy->getScore();
				auto nodeScore = this->getChildByTag(LBL_SCORE_TAG);
				auto lblScore = dynamic_cast<Label *>(nodeScore);
				std::string strScore = StringUtils::format("%d", m_totalScore);
				lblScore->setString(strScore);
			}
			m_totalBombCount--;
			this->updateBomb();
			this->m_enemys.clear();
		}
		
	});
	
	auto lblCount = Label::createWithBMFont("font.fnt", StringUtils::format("X%d", m_totalBombCount));
	lblCount->setPosition(35+lblCount->getContentSize().width/2, 32);
	//lblX->setPosition(20, bomb->getPositionY() + lblX->getContentSize().height);
	this->addChild(lblCount, UI_ZORDER, BOMBCOUNT_TAG);
	//lblX->setColor(Color3B(200, 2, 100));
	lblCount->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	//��ͣ�˵�
	auto SpPauseNormal = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	auto SpPauseSelected = Sprite::createWithSpriteFrameName("game_pause_pressed.png");
	auto SpResumeNormal = Sprite::createWithSpriteFrameName("game_resume_nor.png");
	auto SpResumeSelected = Sprite::createWithSpriteFrameName("game_resume_pressed.png");
	auto itemPause = MenuItemSprite::create(SpPauseNormal, SpPauseSelected);
	auto itemResume = MenuItemSprite:: create(SpResumeNormal, SpResumeSelected);

	auto toggle = MenuItemToggle::createWithCallback([this] (Ref *sender) {
		//��ȡ��ǰѡ������±꣨0��ʼ��
		int index = dynamic_cast<MenuItemToggle *>(sender)->getSelectedIndex();
		if (index) {
			log("Resume");
			Director::getInstance()->pause();
			this->IsPause = 1;
		}
		else {
			log("Pause");
			Director::getInstance()->resume();
			this->IsPause = 0;
		}
	},itemPause,itemResume,nullptr);
	toggle->setPosition(VISIBLE_SIZE - toggle->getContentSize()*1.5);

	auto menu = Menu::create();
	menu->addChild(itemBomb, UI_ZORDER, ITEMBOMB_TAG);
	menu->addChild(toggle);
	menu->setPosition(itemBomb->getContentSize() / 2);
	this->addChild(menu, UI_ZORDER, MENU_TAG);

	//ÿ֡����update����
	scheduleUpdate();
	//��ʱ�����ӵ�
	schedule(schedule_selector(GameScene::createBullet), TIME_BREAK_1);
	//��ʱ�����л�
	schedule(schedule_selector(GameScene::createSmallEnemy), TIME_BREAK_2,CC_REPEAT_FOREVER, CREATE_SMALL_DELAY);
	schedule(schedule_selector(GameScene::createMiddleEnemy), TIME_BREAK_4, CC_REPEAT_FOREVER, CREATE_MIDDLE_DELAY);
	schedule(schedule_selector(GameScene::createBigEnemy), TIME_BREAK_5, CC_REPEAT_FOREVER, CREATE_BIG_DELAY);
	schedule(schedule_selector(GameScene::createUFO), TIME_BREAK_6, CC_REPEAT_FOREVER, CREATE_UFO_DELAY);

	return true;
}
//����������
void GameScene::update(float delta) {
	
	auto bg = this->getChildByTag(1);

	auto bg2 = this->getChildByTag(2);

	auto plane = this->getChildByTag(4);

	
	//�ñ���ͼ2����ͼ1������ȡ����1��λ�ü��ϱ���1�ĸ߶ȣ�
		bg->setPositionY(bg->getPositionY() - BACKGROUND_SPEED);
		bg2->setPositionY(bg->getPositionY() + bg->getContentSize().height);

		//�ñ���ͼ2����ͼ1������ȡ����1��λ�ü��ϱ���1�ĸ߶ȣ�
		bg2->setPositionY(bg->getPositionY() + bg->getContentSize().height);
		//��ͼ2����ײ�ʱ������ͼһ��yֵΪ0��
		if (bg2->getPositionY()<= 0) 
		{
			bg->setPositionY(0);
		}
		
		Vector<Sprite *> removableBullets;
		Vector<Enemy *> removableEnemys;
		Vector<Sprite *> removableUfos;
		/*Vector<Enemy *> removableEnemys2;
		Vector<Enemy *> removableEnemys3;*/
		//�����ӵ�
		for (auto bullet:m_bullets)
		{
			bullet->setPositionY(bullet->getPositionY() + BULLET_SPEED);
			//����ӵ��Ƿ����Ļ����
			if (bullet->getPositionY() >= VISIBLE_SIZE.height+bullet->getContentSize().height/2) {
				this->removeChild(bullet);
				//�����ڱ�������ʱ���޸ļ��ϵĳ�Ա���������Խ����ǰ���Ч�ӵ���ŵ���ʱ�����У��ȱ�������֮���ٴӼ������Ƴ�
				removableBullets.pushBack(bullet);
			}
		}
		
		
		////�����л�
		for (auto eneny : m_enemys) {
			eneny->move();
			if (eneny->getPositionY()<=0-eneny->getContentSize().height / 2) {
				this->removeChild(eneny);
				//�����ڱ�������ʱ���޸ļ��ϵĳ�Ա���������Խ����ǰ���Ч�ӵ���ŵ���ʱ�����У��ȱ�������֮���ٴӼ������Ƴ�
				removableEnemys.pushBack(eneny);
			}
		}

		///��������
		for (auto Ufo : m_UFO)
		{
			

			if (Ufo->getPositionY() >= 600) {
				Ufo->setPositionY(Ufo->getPositionY() - 1);
			}
			else {
				Ufo->setPositionY(Ufo->getPositionY() - UFO_SPEED);
			}
			//�������Ƿ����Ļ�������߽Ӵ����ɻ�
			if (Ufo->getPositionY() <= 0 - Ufo->getContentSize().height / 2) {
				this->removeChild(Ufo);
				removableUfos.pushBack(Ufo);
			}
			if (plane->getBoundingBox().intersectsRect(Ufo->getBoundingBox()) ){
				this->removeChild(Ufo);
				if (this->m_ufoType) {
					m_doubleBulletCount = DOUBLE_BULLET_COUNT;
				}
				else if(m_totalBombCount<3){
					m_totalBombCount++;
					this->updateBomb();
				}
				
				//schedule(schedule_selector(GameScene::createTwoBullet), TIME_BREAK_1, 50,1);
				//�����ڱ�������ʱ���޸ļ��ϵĳ�Ա���������Խ����ǰ���Ч�ӵ���ŵ���ʱ�����У��ȱ�������֮���ٴӼ������Ƴ�
				removableUfos.pushBack(Ufo);
			}
		}

		
		
		//��ײ���
		for (auto enemy : m_enemys) {
			for (auto bullet : m_bullets) {
				if (enemy->getBoundingBox().intersectsRect(bullet->getBoundingBox())) {
					enemy->hit();
					if (enemy->hit()) {
						removableEnemys.pushBack(enemy);
						//���µ÷�
						m_totalScore += enemy->getScore();
						auto nodeScore = this->getChildByTag(LBL_SCORE_TAG);
						auto lblScore = dynamic_cast<Label *>(nodeScore);
						std::string strScore = StringUtils::format("%d", m_totalScore);
						lblScore->setString(strScore);
						
						//lblScore->setColor(Color3B(200, 2, 100));
					}
					
					removableBullets.pushBack(bullet);
					
					this->removeChild(bullet);
				}
			}
			if (enemy->getBoundingBox().intersectsRect(plane->getBoundingBox())) {
				auto ani = Animation::create();

				//  b.��Ӷ���֡,�Ӿ���֡�����в��ҳ�����
				for (int i = 0; i < 4; i++) {
					auto frameName = StringUtils::format("hero_blowup_n%d.png", i + 1);
					ani->addSpriteFrame(CCSpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
				}
				//  c.���ö����л�ʱ��
				ani->setDelayPerUnit(TIME_BREAK_3);
				//  d.���õ�������
				ani->setLoops(1);
				//2.��������װΪ����
				auto animator = Animate::create(ani);
				plane->runAction(animator);
			}
			
		}


		for (auto bullet : removableBullets) {
			m_bullets.eraseObject(bullet);
		}
		removableBullets.clear();
		
		for (auto enemy : removableEnemys) {
			m_enemys.eraseObject(enemy);
		}
		removableEnemys.clear();

		for (auto Ufo : removableUfos) {
			m_UFO.eraseObject(Ufo);
		}

		removableUfos.clear();

}
		
void GameScene::createBullet(float) {
	auto plane = this->getChildByTag(PLANE_TAG);
	if (m_doubleBulletCount > 0) {
		//����˫���ӵ�
		auto bullet1 = Sprite::createWithSpriteFrameName("bullet2.png");
		auto bullet2 = Sprite::createWithSpriteFrameName("bullet2.png");
		bullet1->setPosition(plane->getPositionX() - 32, plane->getPositionY() + 22);
		bullet2->setPosition(plane->getPositionX() + 32, plane->getPositionY() + 22);
		this->addChild(bullet1, FOREROUND_ZORDER);
		this->addChild(bullet2, FOREROUND_ZORDER);
		//�½����ӵ����뼯��
		m_bullets.pushBack(bullet1);
		m_bullets.pushBack(bullet2);
		//���ĵ�˫�ӵ�����Ŀ
		this->m_doubleBulletCount--;
	}
	else {
		auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");
		bullet->setPosition(plane->getPositionX() + 2, plane->getPositionY() + plane->getContentSize().height / 2 + 10);
		this->addChild(bullet, FOREROUND_ZORDER);
		//�½����ӵ����뼯��
		m_bullets.pushBack(bullet);
	}
	
}

/*void GameScene::createTwoBullet(float) {
	auto plane = this->getChildByTag(PLANE_TAG);
	auto bullet1 = Sprite::createWithSpriteFrameName("bullet2.png");
	auto bullet2 = Sprite::createWithSpriteFrameName("bullet2.png");
	bullet1->setPosition(plane->getPositionX() - 32, plane->getPositionY() + 22);
	bullet2->setPosition(plane->getPositionX() + 32, plane->getPositionY() + 22);
	this->addChild(bullet1, FOREROUND_ZORDER);
	this->addChild(bullet2, FOREROUND_ZORDER);
	//�½����ӵ����뼯��
	m_bullets.pushBack(bullet1);
	m_bullets.pushBack(bullet2);
}*/
void GameScene::createEnemy(const EnemyType& type) {
	auto enemy = Enemy::create(type);	
	auto minX = enemy->getContentSize().width / 2;
	auto maxX = VISIBLE_SIZE.width - minX;
	auto x = rand() % (int)(maxX-minX+1)+minX;
	auto y = VISIBLE_SIZE.height+enemy->getContentSize().height/2;
	enemy->setPosition(x, y);	
	this->addChild(enemy, FOREROUND_ZORDER, ENEMY_TAG);
	m_enemys.pushBack(enemy);
}

///�л�
void GameScene::createSmallEnemy(float) {
	this->createEnemy(EnemyType::SMALL_ENEMY);
}

void GameScene::createMiddleEnemy(float) {
	this->createEnemy(EnemyType::MIDDLE_ENEMY);
}

void GameScene::createBigEnemy(float) {
	this->createEnemy(EnemyType::BIG_ENEMY);
}

///����
void GameScene::createUFO(float) {
	this->m_ufoType = rand() % 2;
	std::string frameName = this->m_ufoType ? "ufo1.png" : "ufo2.png";
	auto Ufo = Sprite::createWithSpriteFrameName(frameName);

	auto minX = Ufo->getContentSize().width / 2;
	auto maxX = VISIBLE_SIZE.width - minX;
	auto x = rand() % (int)(maxX - minX + 1) + minX;
	auto y = VISIBLE_SIZE.height + Ufo->getContentSize().height / 2;
	//auto x2 = rand() % (int)(maxX2 - minX2 + 1) + minX2;
	Ufo->setPosition(x, y);
	this->addChild(Ufo, FOREROUND_ZORDER);
	//�½��ĵ��߼��뼯��
	m_UFO.pushBack(Ufo);
}

/*
	1.��ը����Ϊ��ʱ���˵���ͱ�ǩ������ʾ
	2.��ը����Ϊ1ʱ��ֻ��ʾ�˵���
	3.���˵���Ϊ3ʱ����ʾ�˵���ͱ�ǩ�����±�ǩ����
*/

void GameScene::updateBomb() {
	
	auto menu = this->getChildByTag(MENU_TAG);
	auto itemBomb = menu->getChildByTag(ITEMBOMB_TAG);//ע��������menu��ȡitemBomb
	auto lblCount = this->getChildByTag(BOMBCOUNT_TAG);
	if (this->m_totalBombCount <= 0) {
		itemBomb->setVisible(false);
		lblCount->setVisible(false);
	}
	else if (this->m_totalBombCount == 1) {
		itemBomb->setVisible(true);
		lblCount->setVisible(false);
	}
	else {
		itemBomb->setVisible(true);
		lblCount->setVisible(true);
		//����ǿת�ɸ������
		dynamic_cast<Label *>(lblCount)->setString(StringUtils::format("X%d", this->m_totalBombCount));
	}
}