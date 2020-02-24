#include "QuestWindow.h"
#include "oxygine-framework.h"


Questwindow::Questwindow()
{
	res.loadXML("res.xml");
	spSprite questWindow = new Sprite();

	//Основное окно к которому прикрепляются все остальные объекты. В данном случае оно занимает 60% по х и 85% по y от размера сцены.
	questWindow->setResAnim(res.getResAnim("OxyMain"));
	questWindow->setSize(getStage()->getSize().x / 100 * 60, getStage()->getSize().y / 100 * 85);
	questWindow->setAnchor(0.5, 0.5);

	//Здесь это окно помещается в центр сцены.
	Vector2 pos = getStage()->getSize() / 2;
	questWindow->setPosition(pos);
	addChild(questWindow);

	std::string borders_img[4] = { "border_top_left" ,"border_top_right","border_down_left","border_down_right"};
	//int massive_x = questWindow->getSize().x / res.getResAnim("border_top_left")->getSize().x;
	int massive_x = getStage()->getSize().x / 100 * 70;
	int massive_y = getStage()->getSize().y / 100 * 70;
	pos = { 0,0 };
	bool x = true;
	int j = 0;
	spSprite *borders_sprite = new spSprite[massive_x*2+massive_y*2+1];

	float size_x = getStage()->getSize().x/(getStage()->getSize().x / 100 * 70/2);

	while (true) {
		borders_sprite[j] = new Sprite();
		if (x){
			if (pos.y == 0 && pos.x >= questWindow->getSize().x) { pos = { 0,questWindow->getSize().y - borders_sprite[0]->getSize().y }; }
			else if (pos.x >= questWindow->getSize().x && pos.y == questWindow->getSize().y - borders_sprite[0]->getSize().y) { pos = {0,0}; x = false; }
			else{
				borders_sprite[j]->setResAnim(res.getResAnim("border_main_top_down"));
				borders_sprite[j]->attachTo(questWindow);
				borders_sprite[j]->setSize(size_x, size_x);
				borders_sprite[j]->setPosition(pos);
			}
			pos = { borders_sprite[j]->getPosition().x+ borders_sprite[j]->getSize().x , pos.y};
		}
		else {
			if (pos.y >= questWindow->getSize().y - borders_sprite[0]->getSize().y && pos.x == 0){
				pos = { questWindow->getSize().x- borders_sprite[0]->getSize().x, 0 }; 
			}
			else if (pos.y >= questWindow->getSize().y - borders_sprite[0]->getSize().y) { break; }
			else {
				borders_sprite[j]->setResAnim(res.getResAnim("border_main_left_right"));
				borders_sprite[j]->attachTo(questWindow);
				borders_sprite[j]->setSize(size_x, size_x);
				borders_sprite[j]->setPosition(pos);
				pos = { pos.x , borders_sprite[j]->getPosition().y + borders_sprite[j]->getSize().y };
			}
		}
		j += 1;
	}

	for (int j = 0; j <= massive_x * 2 + massive_y * 2;j++) {
		if (x) {
			if (j==massive_x){ pos = { 0,questWindow->getSize().y }; }
			else if(pos.x >= questWindow->getSize().x && pos.y == questWindow->getSize().y) { pos = { 0,0 }; x = false; }

			else {
				borders_sprite[j]->setResAnim(res.getResAnim("border_main_top_down"));
				borders_sprite[j]->attachTo(questWindow);
				borders_sprite[j]->setPosition(pos);
			}
		}
	}

	spSprite border_top_left = new Sprite();
	border_top_left->setResAnim(res.getResAnim("border_top_left"));
	border_top_left->attachTo(questWindow);
	border_top_left->setSize(size_x, size_x);
	border_top_left->setPosition(0, 0);

	spSprite border__top_right = new Sprite();
	border__top_right->setResAnim(res.getResAnim("border_top_right"));
	border__top_right->attachTo(questWindow);
	border__top_right->setSize(size_x, size_x);
	border__top_right->setPosition(questWindow->getSize().x - border__top_right->getSize().x, 0);

	spSprite border_bot_left = new Sprite();
	border_bot_left->setResAnim(res.getResAnim("border_down_left"));
	border_bot_left->attachTo(questWindow);
	border_bot_left->setSize(size_x, size_x);
	border_bot_left->setPosition(0, questWindow->getSize().y - border_bot_left->getSize().y);

	spSprite border_bot_right = new Sprite();
	border_bot_right->setResAnim(res.getResAnim("border_down_right"));
	border_bot_right->attachTo(questWindow);
	border_bot_right->setSize(size_x, size_x);
	border_bot_right->setPosition(questWindow->getSize().x - border_bot_right->getSize().x, questWindow->getSize().y - border_bot_right->getSize().y);








}

Questwindow::~Questwindow()
{
	res.free();

}