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
	int massive_x = questWindow->getSize().x / res.getResAnim("border_top_left")->getSize().x;
	int massive_y = questWindow->getSize().y / res.getResAnim("border_main_left_right")->getSize().y;
	pos = { 0,0 };
	bool x = true;
	int j = 0;
	spSprite *borders_sprite = new spSprite[massive_x*2+massive_y*2+10];

	while (true) {
		borders_sprite[j] = new Sprite();
		if (x){
			if (j == massive_x) { pos = { 0,questWindow->getSize().y }; }
			else if (pos.x >= questWindow->getSize().x && pos.y == questWindow->getSize().y) { pos = {0,0}; x = false; }
			else{
				borders_sprite[j]->setResAnim(res.getResAnim("border_main_top_down"));
				borders_sprite[j]->attachTo(questWindow);
				borders_sprite[j]->setPosition(pos);
			}
			pos = { borders_sprite[j]->getPosition().x+ borders_sprite[j]->getSize().x , pos.y};
		}
		else {
			if (pos.y >= questWindow->getSize().y && pos.x == 0){
				pos = { questWindow->getSize().x- borders_sprite[0]->getSize().x, 0 }; 
			}
			else if (pos.y >= questWindow->getSize().y ) { break; }
			else {
				borders_sprite[j]->setResAnim(res.getResAnim("border_main_left_right"));
				borders_sprite[j]->attachTo(questWindow);
				borders_sprite[j]->setPosition(pos);
				pos = { pos.x , borders_sprite[j]->getPosition().y + borders_sprite[j]->getSize().y };
			}
		}
		j += 1;
	}


	spSprite border_top_left = new Sprite();
	border_top_left->setResAnim(res.getResAnim("border_top_left"));
	border_top_left->attachTo(questWindow);
	border_top_left->setPosition(0, 0);

	spSprite border__top_right = new Sprite();
	border__top_right->setResAnim(res.getResAnim("border_top_right"));
	border__top_right->attachTo(questWindow);
	border__top_right->setPosition(questWindow->getSize().x - border__top_right->getSize().x, 0);

	spSprite border_bot_left = new Sprite();
	border_bot_left->setResAnim(res.getResAnim("border_down_left"));
	border_bot_left->attachTo(questWindow);
	border_bot_left->setPosition(0, questWindow->getSize().y);

	spSprite border_bot_right = new Sprite();
	border_bot_right->setResAnim(res.getResAnim("border_down_right"));
	border_bot_right->attachTo(questWindow);
	border_bot_right->setPosition(questWindow->getSize().x - border_bot_right->getSize().x, questWindow->getSize().y);

/*

			if (j == 0 || j == massive_x-1 || j == massive_x || j == massive_x*2-1){
				if (j == massive_x) { pos = { 0,questWindow->getSize().y }; }
				borders_sprite[j]->setResAnim(res.getResAnim(borders_img[img]));
				borders_sprite[j]->attachTo(questWindow);
				borders_sprite[j]->setPosition(pos);
				img += 1;
			}
	//Верхняя шапка, где обычно располагаются кнопка закрыть окно. Имеет х основного окна. По y значение статично.
	spSprite header = new Sprite();
	header->setResAnim(res.getResAnim("OxyHeader"));
	header->attachTo(questWindow);
	header->setSize(questWindow->getSize().x, 17);

	//Окно, где обычно располагается список всех квестов. Имеет размер 44% по х от основного окна.
	spSprite questList = new Sprite();
	questList->setResAnim(res.getResAnim("OxyQuests"));
	questList->attachTo(questWindow);
	questList->setSize(questWindow->getSize().x/100*44, questWindow->getSize().y- header->getSize().y);
	questList->setPosition(0, header->getSize().y);

	//Окно описания квеста. По х имеет такой размер, чтобы атоматически заполнять пустое пространство справа от списка квестов. Меняется динамически в зависимости от размера списка квестов по х.
	spSprite questDescription = new Sprite();
	questDescription->setResAnim(res.getResAnim("OxyDescription"));
	questDescription->attachTo(questWindow);
	questDescription->setSize(questWindow->getSize().x / 100 * (100-(questList->getSize().x/questWindow->getSize().x * 100)), questWindow->getSize().y - header->getSize().y);
	questDescription->setPosition(questList->getSize().x, header->getSize().y);

	//Линия в описании квеста отделяющая описание от награды. По х имеет размер в 90% от х окна описания квеста. По y значение статично.
	spSprite questDescriptionLine = new Sprite();
	questDescriptionLine->setResAnim(res.getResAnim("OxyLine"));
	questDescriptionLine->attachTo(questDescription);
	questDescriptionLine->setSize(questDescription->getSize().x / 100 * 90, 5);
	questDescriptionLine->setPosition(questDescription->getSize().x / 100 * 5, questDescription->getSize().y - 246);
	*/






}

Questwindow::~Questwindow()
{
	res.free();

}