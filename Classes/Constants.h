#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define VISIBLE_SIZE Director::getInstance()->getVisibleSize()
#define VISIBLE_ORIGIN Director::getInstance()->getVisibleOrigin()

//��ǩ
#define BACKGROUND_TAG_1 1
#define BACKGROUND_TAG_2 2
#define ENEMY_TAG 3
#define PLANE_TAG 4
#define LBL_SCORE_TAG 10
#define UFO_TAG 11
#define MENU_TAG 12
#define BOMBCOUNT_TAG 13
#define ITEMBOMB_TAG 20

//ZORDER
#define BACKGROUND_ZORDER -1
#define DEFAULT_ZORDER 0
#define FOREROUND_ZORDER 1
#define UI_ZORDER 99

//��ʱ����س���
#define TIME_BREAK_1 0.2f
#define TIME_BREAK_2 1.1f
#define TIME_BREAK_3 0.05f
#define TIME_BREAK_4 5.0f
#define TIME_BREAK_5 25.0f
#define TIME_BREAK_6 30.0f
#define CREATE_SMALL_DELAY 3
#define CREATE_MIDDLE_DELAY 10
#define CREATE_BIG_DELAY 20
#define CREATE_UFO_DELAY 15

//�ٶ�
#define BACKGROUND_SPEED 0.8f
#define SMALL_ENEMY_SPEED 4
#define MIDDLE_ENEMY_SPEED 2
#define BIG_ENEMY_SPEED 1
#define BULLET_SPEED 6
#define UFO_SPEED 3

//˫�ӵ��Ĵ���
#define DOUBLE_BULLET_COUNT 30

//��������
#define HERO_FLY_ANIMATION "HEROFLY"
#define BIG_ENEMY_FLY_ANIMATION "BIGENEMYFLY"
#define MIDDLE_ENEMY_HIT_ANIMATION "MIDDLEENEMYHIT"
#define BIG_ENEMY_DOWN_ANIMATION "BIGENEMYDOWN"
#define MIDDLE_ENEMY_DOWN_ANIMATION "MIDDLEENEMYDOWN"
#define SMALL_ENEMY_DOWN_ANIMATION "SMALLENEMYDOWN"
#define BIG_ENEMY_HIT_ANIMATION "BIGENEMYHIT"

#define HIGHSCORE "HIGHSCORE"
#endif